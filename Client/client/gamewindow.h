#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QString>
#include <QTcpSocket>
#include <QDialog>
#include <QWidget>
#include <vector>
#include "buildablelabel.h"
#include "stats.h"
#include "highlightedlabel.h"
#include "choosetower.h"

using namespace std;

namespace Ui {
class GameWindow;
}

class GameWindow : public QDialog
{
    Q_OBJECT

    int team, lblWidth, lblHeight;
    ChooseTower *tower1, *tower2, *tower3;
    QWidget *parent, *gameDisplay, *actionDisplay;
    QPushButton *btn;
    Ui::GameWindow* ui;
    QTcpSocket* socket;
    bool unexpected, windowSized;
    vector<Stats> stats;

    void getTileInfo(QString);
    void getBuildingInfo(QString);
    void getUnitInfo(QString);
    void getPlayerInfo(QString);
    void createBuilding(QString);
    void getPlayerHealth(QString);
    void getPlayerMoney(QString);
    void getPlayerHealthMoney(QString);
    void getBuildingUpgrade(QString);
    void getBuildingDeath(QString);
    void getUnitCreation(QString);
    void getUnitMove(QString);
    void getUnitMoveTurn(QString);
    void getUnitMoveHealth(QString);
    void getUnitMoveTurnHealth(QString);
    void getUnitDeath(QString);
    void getBulletInfo(QString);
    void doGamePause();

    void displayBuildingInfo();

    Stats getStatsByType(QString type);

public:
    explicit GameWindow(QString&, QWidget* = 0,  QTcpSocket* = 0);

    BuildableLabel* getClickedLabel();
    ChooseTower* getTowerChosen();

    void createButton();

    void updateGameState(QString);
    ~GameWindow();

private slots:
    void serverDisconnected();

    void dataReceived();

    void on_btnExitGame_clicked();

    void on_btn_clicked();
};

#endif // GAMEWINDOW_H
