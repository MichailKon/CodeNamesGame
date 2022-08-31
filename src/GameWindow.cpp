#include "GameWindow.h"
#include "ui_GameWindow.h"
#include "GameWorker.h"
#include "FieldPlane.h"
#include "ClickableLabel.h"
#include <QMetaEnum>

GameWindow::GameWindow(QWidget *parent) :
    QWidget(parent), ui(new Ui::GameWindow) {
    ui->setupUi(this);
    m_worker = new GameWorker(tr(""));
    setCurTeamLabelStyle(m_worker->curTeam());
    connect(ui->pushButton_showField, &QPushButton::clicked, this, &GameWindow::showField);
    connect(m_worker, &GameWorker::teamWin, this, &GameWindow::gameEnd);
    connect(ui->pushButton_endMove, &QPushButton::clicked, [&]() {
        m_worker->endMove();
        ui->label_curTeam->setText(QMetaEnum::fromType<GameWorker::TeamName>().valueToKey(m_worker->curTeam()));
        setCurTeamLabelStyle(m_worker->curTeam());
    });

    setStyleSheet("QLabel[type=\"field-label\"] { border: 1px solid black;  border-radius: 3px; }");

    for (int i = 0; i < GameWorker::FIELD_HEIGHT; i++) {
        m_labels.emplace_back();
        for (int j = 0; j < GameWorker::FIELD_WIDTH; j++) {
            auto label = new ClickableLabel(this);
            label->setAlignment(Qt::AlignCenter);

            label->setText(tr("Label (%1; %2)").arg(i).arg(j));
            label->setProperty("type", "field-label");
            label->setProperty("row", i);
            label->setProperty("col", j);

            m_labels.back().emplace_back(label);
            ui->gridLayout_2->addWidget(label, i, j);
            connect(label, &ClickableLabel::doubleClicked, this, &GameWindow::cardClicked);
        }
    }
    ui->label_curTeam->setText(QMetaEnum::fromType<GameWorker::TeamName>().valueToKey(m_worker->curTeam()));
}

GameWindow::~GameWindow() {
    delete ui;
    m_worker->deleteLater();
    for (auto &i : m_labels) for (auto &j : i) j->deleteLater();
    if (pushButton_sendHint) pushButton_sendHint->deleteLater();
}

void GameWindow::cardClicked() {
    auto *label = (ClickableLabel *) sender();
    int i = label->property("row").toInt();
    int j = label->property("col").toInt();
    if (m_worker->openCard(i, j) != GameWorker::Invalid) {
        switch (m_worker->getType(i, j)) {
            case GameWorker::BlueCard:
                m_labels[i][j]->setStyleSheet("color: blue");
                break;
            case GameWorker::RedCard:
                m_labels[i][j]->setStyleSheet("color: red");
                break;
            case GameWorker::WhiteCard:
                m_labels[i][j]->setStyleSheet("color: silver");
                break;
            case GameWorker::BlackCard:
                m_labels[i][j]->setStyleSheet("color: black");
                break;
            case GameWorker::Invalid:
                Q_UNREACHABLE();
        }
        label->blockSignals(true);
    }
    if (!m_worker->isGameEnded())
        ui->label_curTeam->setText(QMetaEnum::fromType<GameWorker::TeamName>().valueToKey(m_worker->curTeam()));
    setCurTeamLabelStyle(m_worker->curTeam());
}

void GameWindow::showField() {
    auto *plane = new FieldPlane();
    plane->setWorker(m_worker);
    plane->showField();
    plane->show();
    connect(plane, &QDialog::finished, plane, &QDialog::deleteLater);
}

void GameWindow::gameEnd(const GameWorker::TeamName &winTeam) {
    ui->label_curTeam
        ->setText(tr("Team %1 wins!").arg(QMetaEnum::fromType<GameWorker::TeamName>().valueToKey(winTeam)));
    // block labels
    ui->pushButton_endMove->setDisabled(true);
    for (int i = 0; i < GameWorker::FIELD_HEIGHT; i++) {
        for (int j = 0; j < GameWorker::FIELD_WIDTH; j++) {
            m_labels[i][j]->blockSignals(true);
            /*switch (m_worker->getType(i, j)) {
                case GameWorker::BlueCard:
                    m_labels[i][j]->setStyleSheet("color: blue");
                    break;
                case GameWorker::RedCard:
                    m_labels[i][j]->setStyleSheet("color: red");
                    break;
                case GameWorker::WhiteCard:
                    m_labels[i][j]->setStyleSheet("color: silver");
                    break;
                case GameWorker::BlackCard:
                    m_labels[i][j]->setStyleSheet("color: black");
                    break;
                case GameWorker::Invalid:
                    Q_UNREACHABLE();
            }*/
        }
    }
}

void GameWindow::setCurTeamLabelStyle(const GameWorker::TeamName &team) {
    if (team == GameWorker::BlueTeam) {
        ui->label_curTeam->setStyleSheet("color: blue");
    } else {
        ui->label_curTeam->setStyleSheet("color: red");
    }
}
