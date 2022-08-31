#include "GameWorker.h"
#include <QRandomGenerator>
#include <QtAlgorithms>

GameWorker::GameWorker(const QStringView &path) : m_curTeam(BlueTeam), m_gameEnded(false) {
    QVector<QPair<QString, CardType>> cards1D;
    m_isOpened.resize(FIELD_HEIGHT, QVector<bool>(FIELD_WIDTH));

    cards1D.reserve(FIELD_HEIGHT * FIELD_WIDTH);
    for (int i = 0; i < BLUE_CARDS; i++) {
        cards1D.emplace_back("cock.jpg", BlueCard);
    }
    for (int i = 0; i < RED_CARDS; i++) {
        cards1D.emplace_back("cock.jpg", RedCard);
    }
    for (int i = 0; i < WHITE_CARDS; i++) {
        cards1D.emplace_back("cock.jpg", WhiteCard);
    }
    for (int i = 0; i < BLACK_CARDS; i++) {
        cards1D.emplace_back("cock.jpg", BlackCard);
    }

    std::shuffle(cards1D.begin(), cards1D.end(), QRandomGenerator(QRandomGenerator::system()->generate()));

    m_images.resize(FIELD_HEIGHT);
    m_types.resize(FIELD_HEIGHT);
    int row = 0, col = 0;

    for (auto &i: cards1D) {
        m_images[row] << i.first;
        m_types[row] << i.second;
        col++;
        if (col == FIELD_WIDTH) {
            col = 0, row++;
        }
    }
}

GameWorker::~GameWorker() = default;

QString GameWorker::getImage(int i, int j) const {
    return m_images[i][j];
}

GameWorker::CardType GameWorker::openCard(int i, int j) {
    if (i < 0 || j < 0 || i >= FIELD_HEIGHT || j >= FIELD_WIDTH || m_isOpened[i][j]) {
        return Invalid;
    }
    m_isOpened[i][j] = true;
    m_blueOpened += m_types[i][j] == BlueCard;
    m_redOpened += m_types[i][j] == RedCard;
    if (m_blueOpened == BLUE_CARDS) {
        m_gameEnded = true;
        emit teamWin(BlueTeam);
        return BlueCard;
    }
    if (m_redOpened == RED_CARDS) {
        m_gameEnded = true;
        emit teamWin(RedTeam);
        return RedCard;
    }
    if (m_types[i][j] == BlackCard) {
        m_gameEnded = true;
        if (m_curTeam == RedTeam) {
            emit teamWin(BlueTeam);
        } else {
            emit teamWin(RedTeam);
        }
    }
    if (m_curTeam == BlueTeam) {
        if (m_types[i][j] != BlueCard) {
            m_curTeam = RedTeam;
        }
    } else {
        if (m_types[i][j] != RedCard) {
            m_curTeam = BlueTeam;
        }
    }
    return m_types[i][j];
}

GameWorker::CardType GameWorker::getType(int i, int j) const {
    return m_types[i][j];
}

GameWorker::TeamName GameWorker::curTeam() const {
    return m_curTeam;
}

bool GameWorker::isCellOpened(int i, int j) const {
    return m_isOpened[i][j];
}

bool GameWorker::isGameEnded() const {
    return m_gameEnded;
}

void GameWorker::endMove() {
    if (m_curTeam == BlueTeam) {
        m_curTeam = RedTeam;
    } else {
        m_curTeam = BlueTeam;
    }
}
