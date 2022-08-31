#ifndef CODENAMESGAME_GAMEWORKER_H
#define CODENAMESGAME_GAMEWORKER_H

#include <QObject>

class GameWorker : public QObject {
Q_OBJECT

public:
    static const int FIELD_WIDTH = 5;
    static const int FIELD_HEIGHT = 4;
    static const int BLUE_CARDS = 8;
    static const int RED_CARDS = 7;
    static const int WHITE_CARDS = 4;
    static const int BLACK_CARDS = 1;

    enum CardType {
        BlueCard,
        RedCard,
        WhiteCard,
        BlackCard,
        Invalid
    };
    Q_ENUM(CardType);

    enum TeamName {
        RedTeam,
        BlueTeam
    };
    Q_ENUM(TeamName);

    explicit GameWorker(const QStringView &imagesPath);

    ~GameWorker() override;

    [[nodiscard]] QString getImage(int i, int j) const;

    [[nodiscard]] CardType getType(int i, int j) const;

    [[nodiscard]] GameWorker::TeamName curTeam() const;

    [[nodiscard]] bool isCellOpened(int i, int j) const;

    void endMove();

    [[nodiscard]] bool isGameEnded() const;

public slots:

    GameWorker::CardType openCard(int i, int j);

signals:

    void teamWin(const GameWorker::TeamName &name);

private:
    TeamName m_curTeam;
    QVector<QStringList> m_images;
    QVector<QVector<CardType>> m_types;
    QVector<QVector<bool>> m_isOpened;
    int m_blueOpened{}, m_redOpened{};
    bool m_gameEnded;
};

#endif //CODENAMESGAME_GAMEWORKER_H
