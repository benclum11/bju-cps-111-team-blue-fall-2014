#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QString>
#include <QTcpSocket>
#include <QDialog>
#include <QWidget>
#include <vector>
#include <QTextEdit>
#include <QMessageBox>
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
    ChooseTower *unit1, *unit2, *unit3;
    QWidget *parent, *gameDisplay, *actionDisplay;
    QPushButton *btn, *btnUnits, *saveGame, *startBtn, *cheatBtn;
    QTextEdit *filename;
    QLabel *money, *health, *enemyHealth; //label that displays money/health
    Ui::GameWindow* ui;
    QTcpSocket* socket;
    bool unexpected, windowSized;
    vector<Stats> stats;

    void createLabelsandButtons();

    void getTileInfo(QString);
    void getBuildingInfo(QString);
    void getUnitInfo(QString);
    void getPlayerInfo(QString);
    void createBuilding(QString);
    void getPlayerHealth(QString);
    void getPlayerMoney(QString);
    void getUnitCreation(QString);
    void getUnitHealth(QString);
    void getUnitMove(QString);
    void getUnitMoveTurn(QString);
    void getUnitDeath(QString);
    void doGamePause();

//Deprecated methods
/*
    void getBuildingUpgrade(QString);
    void getBuildingDeath(QString);
    void getUnitMoveTurnHealth(QString);
    void getBulletInfo(QString);
*/

    void displayBuildingInfo();

    Stats getStatsByType(QString type);

public:

    explicit GameWindow(QString&, QWidget* = 0,  QTcpSocket* = 0);

    BuildableLabel* getClickedLabel();
    ChooseTower* getTowerChosen();

    void createButton();

    void updateGameState(QString);
    ~GameWindow();

    void doGameOver(QString);

    void changeTimerButton(QString);


    bool isPaused;



private slots:
    void serverDisconnected();

    void dataReceived();

    void on_btnExitGame_clicked();

    void on_btn_clicked();

    void on_btnUnits_clicked();

    void on_saveGame_clicked();

    void on_start_clicked();

    void on_cheat_clicked();
};

#endif // GAMEWINDOW_H
