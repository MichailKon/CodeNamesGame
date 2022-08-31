#ifndef CODENAMESGAME_GAMEWINDOW_H
#define CODENAMESGAME_GAMEWINDOW_H

#include <QWidget>
#include "GameWorker.h"

class GameWorker;

class ClickableLabel;

class QPushButton;

QT_BEGIN_NAMESPACE
namespace Ui { class GameWindow; }
QT_END_NAMESPACE

class GameWindow : public QWidget {
Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);

    ~GameWindow() override;

private slots:

    void cardClicked();

    void showField();

    void gameEnd(const GameWorker::TeamName &winTeam);

private:
    Ui::GameWindow *ui;

    GameWorker *m_worker;
    QVector<QVector<ClickableLabel *>> m_labels;
    QPushButton *pushButton_sendHint{};

    void setCurTeamLabelStyle(const GameWorker::TeamName &team);
};

#endif //CODENAMESGAME_GAMEWINDOW_H
