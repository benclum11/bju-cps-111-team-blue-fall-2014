#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QString>
#include <QPixmap>
#include "buildablelabel.h"
#include "helpwindow.h"
#include <gamelobby.h>

//void MainWindow::getTileInfo(QString command)
//{
//    QStringList commandArgs = command.split(" ");
//    if (!windowSet) {
//        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
//        int winWidth = commandArgs.at(2).toInt() * commandArgs.at(4).toInt();
//        int winHeight = commandArgs.at(3).toInt() * commandArgs.at(5).toInt();
//        resize(winWidth,winHeight);
//        setMinimumWidth(winWidth);
//        setMaximumWidth(winWidth);
//        setMinimumHeight(winHeight);
//        setMaximumHeight(winHeight);
//        setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
//        windowSet = true;
//    }
//    if (windowSet) {
//        QLabel* lbl;
//        QPixmap pixmap;
//        if (commandArgs.at(5) == "0") {
//            lbl = new QLabel(this);
//            lbl->setPixmap(QPixmap("://Resources/Tiles/0.png"));
//        } else if (commandArgs.at(5) == "1" && commandArgs.at(6).toInt() == team) {
//            lbl = new BuildableLabel(this);
//            lbl->setPixmap(QPixmap("://Resources/Tiles/1.png"));
//        } else {
//            lbl = new QLabel(this);
//            lbl->setPixmap(QPixmap("://Resources/Tiles/1.png"));
//        }
//        lbl->setScaledContents(true);
//        int x = commandArgs.at(3).toInt() - lblWidth/2;
//        int y = commandArgs.at(4).toInt() - lblHeight/2;
//        lbl->setGeometry(x,y,lblWidth,lblHeight);
//    }
//}

//void MainWindow::getBuildingInfo(QString command)
//{
//    QStringList commandArgs = command.split(" ");
//}

//void MainWindow::getUnitInfo(QString command)
//{
//    QStringList commandArgs = command.split(" ");
//}

//void MainWindow::getPlayerInfo(QString command)
//{
//    QStringList commandArgs = command.split(" ");
//}

//void MainWindow::createBuilding(QString command)
//{
//    QStringList commandArgs = command.split(" ");
//}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    windowSet(false)
{
    ui->setupUi(this);

    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::readyRead, this, &MainWindow::dataReceived);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//void MainWindow::updateGameState(QString srvrMsg)
//{
//    QStringList commands = srvrMsg.split("%%");
//    for (int i = 0; i < commands.size(); ++i) {
//        QStringList commandargs = commands.at(i).split(" ");
//        int commandType = commandargs.at(0).toInt();
//        switch (commandType) {
//        case 0:
//            team = commands.at(i).split(" ").at(1).toInt();
//            break;
//        case 1:
//            getTileInfo(commands.at(i));
//            break;
//        case 2:
//            getBuildingInfo(commands.at(i));
//            break;
//        case 3:
//            getUnitInfo(commands.at(i));
//            break;
//        case 11:
//            getPlayerInfo(commands.at(i));
//            break;
//        case 14:

//            break;
//        case 16:

//            break;
//        case 17:

//            break;
//        case 21:
//            createBuilding(commands.at(i));
//            break;
//        case 28:

//            break;
//        case 20:

//            break;
//        case 31:

//            break;
//        case 32:

//            break;
//        case 33:

//            break;
//        case 34:

//            break;
//        case 35:

//            break;
//        case 30:

//            break;
//        case 4:

//            break;
//        case 5:

//            break;
//        default:
//            break;
//        }
//    }
//}

void MainWindow::on_btnConnect_clicked()
{
    // Decide to connect to supplied IP or to localhost.
    if (this->ui->lnIPAddr->text().size() == 0)
    {
        socket->connectToHost("localhost", 10000);
    }
    else
    {
        socket->connectToHost(ui->lnIPAddr->text(), 10000);
    }

    if (!socket->waitForConnected())
    {
        QMessageBox::critical(this, "Error", "Unable to connect to server.");
        return;
    }

    launchLobby();
}

void MainWindow::on_btnHelp_clicked()
{
    helpWindow help;
    help.setModal(true);
    help.exec();
}

void MainWindow::on_btnExit_clicked()
{
    this->close();
}

void MainWindow::dataReceived()
{
    QTcpSocket *sock = dynamic_cast<QTcpSocket*>(sender());
    while (sock->canReadLine()) {
        QString str = sock->readLine();
        //updateGameState(str);
    }
}

// Disables connect button and opens the game lobby window
void MainWindow::launchLobby()
{
    gameLobby lobby(this, socket);
    lobby.setModal(true);
    lobby.exec();
}
