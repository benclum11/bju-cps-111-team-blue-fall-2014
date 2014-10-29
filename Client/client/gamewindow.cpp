#include "gamewindow.h"
#include <QLabel>
#include <QPixmap>

GameWindow::GameWindow(QWidget* parent, QTcpSocket* socket) :
    QMainWindow(parent), parent(parent), ui(new Ui::GameWindow),
    socket(socket), unexpected(true)
{
   ui->setupUi(this);
   parent->hide();
   connect(socket, &QTcpSocket::disconnected, this, &GameWindow::serverDisconnected);
}

GameWindow::~GameWindow()
{
    delete ui;
    socket->close();
}

void GameWindow::serverDisconnected()
{

}

void GameWindow::getTileInfo(QString command)
{
    QStringList commandArgs = command.split(" ");
    if (true) {
        gameDisplay = new QWidget(this);
        int gameWidth = commandArgs.at(2).toInt() * commandArgs.at(4).toInt();
        int gameHeight = commandArgs.at(3).toInt() * commandArgs.at(5).toInt();
        gameDisplay->resize(gameWidth,gameHeight);
        gameDisplay->setMinimumWidth(gameWidth);
        gameDisplay->setMaximumWidth(gameWidth);
        gameDisplay->setMinimumHeight(gameHeight);
        gameDisplay->setMaximumHeight(gameHeight);
    }
    if (true) {
        QLabel* lbl;
        QPixmap pixmap;
        if (commandArgs.at(5) == "0") {
            lbl = new QLabel(this);
            lbl->setPixmap(QPixmap("://Resources/Tiles/0.png"));
        } else if (commandArgs.at(5) == "1" && commandArgs.at(6).toInt() == team) {
            lbl = new BuildableLabel(this);
            lbl->setPixmap(QPixmap("://Resources/Tiles/1.png"));
        } else {
            lbl = new QLabel(this);
            lbl->setPixmap(QPixmap("://Resources/Tiles/1.png"));
        }
        lbl->setScaledContents(true);
        int x = commandArgs.at(3).toInt() - lblWidth/2;
        int y = commandArgs.at(4).toInt() - lblHeight/2;
        lbl->setGeometry(x,y,lblWidth,lblHeight);
    }
}

void GameWindow::getBuildingInfo(QString command)
{
    QStringList commandArgs = command.split(" ");
}

void GameWindow::getUnitInfo(QString command)
{
    QStringList commandArgs = command.split(" ");
}

void GameWindow::getPlayerInfo(QString command)
{
    QStringList commandArgs = command.split(" ");
}

void GameWindow::createBuilding(QString command)
{
    QStringList commandArgs = command.split(" ");
}

void GameWindow::updateGameState(QString srvrMsg)
{
    QStringList commands = srvrMsg.split("%%");
    for (int i = 0; i < commands.size(); ++i) {
        QStringList commandargs = commands.at(i).split(" ");
        int commandType = commandargs.at(0).toInt();
        switch (commandType) {
        case 0:
            team = commands.at(i).split(" ").at(1).toInt();
            break;
        case 1:
            getTileInfo(commands.at(i));
            break;
        case 2:
            getBuildingInfo(commands.at(i));
            break;
        case 3:
            getUnitInfo(commands.at(i));
            break;
        case 11:
            getPlayerInfo(commands.at(i));
            break;
        case 14:

            break;
        case 16:

            break;
        case 17:

            break;
        case 21:
            createBuilding(commands.at(i));
            break;
        case 28:

            break;
        case 20:

            break;
        case 31:

            break;
        case 32:

            break;
        case 33:

            break;
        case 34:

            break;
        case 35:

            break;
        case 30:

            break;
        case 4:

            break;
        case 5:

            break;
        default:
            break;
        }
    }
}

