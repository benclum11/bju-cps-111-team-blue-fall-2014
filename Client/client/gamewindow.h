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

    int team, lblWidth, lblHeight;
    QWidget *parent, *gameDisplay;
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
};

#endif // GAMEWINDOW_H
