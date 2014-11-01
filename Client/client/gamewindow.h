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

using namespace std;

namespace Ui {
class GameWindow;
}

class GameWindow : public QDialog
{
    Q_OBJECT

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

    int team, lblWidth, lblHeight;
    QWidget *parent, *gameDisplay, *actionDisplay;
    Ui::GameWindow* ui;
    QTcpSocket* socket;
    bool unexpected, windowSized;
    vector<Stats> stats;

    Stats getStatsByType(QString type);

public:
    explicit GameWindow(QString&, QWidget* = 0,  QTcpSocket* = 0);

    BuildableLabel *getClickedLabel();

    void updateGameState(QString);
    ~GameWindow();

private slots:
    void serverDisconnected();

    void dataReceived();

    void on_btnExitGame_clicked();
};

#endif // GAMEWINDOW_H
