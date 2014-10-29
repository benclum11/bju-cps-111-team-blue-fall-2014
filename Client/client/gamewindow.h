#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "ui_gamewindow.h"
#include <QMainWindow>
#include <QString>
#include <QTcpSocket>
#include "buildablelabel.h"

namespace Ui {
class GameWindow;
}

class GameWindow : public QMainWindow
{
    Q_OBJECT

    void getTileInfo(QString);
    void getBuildingInfo(QString);
    void getUnitInfo(QString);
    void getPlayerInfo(QString);
    void createBuilding(QString);

    int team, lblWidth, lblHeight;
    QWidget* gameDisplay, parent;
    Ui::GameWindow* ui;
    QTcpSocket* socket;
    bool unexpected;

public:
    explicit GameWindow(QWidget* = 0,  QTcpSocket* = 0);

    void updateGameState(QString);
    ~GameWindow();

private slots:
    void serverDisconnected();

};

#endif // GAMEWINDOW_H
