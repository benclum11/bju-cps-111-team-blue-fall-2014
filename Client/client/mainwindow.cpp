#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QString>
#include <QPixmap>
#include "buildablelabel.h"

void MainWindow::getTileInfo(QString command)
{
    QStringList commandArgs = command.split(" ");
    QLabel* lbl;
    QPixmap pixmap;
    if (commandArgs.at(5) == "0") {
        lbl = new QLabel(this);
        lbl->setPixmap(QPixmap("://Resources/Tiles/0.png"));
    } else if (commandArgs.at(5) == "1") {
        lbl = new BuildableLabel(this);
        lbl->setPixmap(QPixmap("://Resources/Tiles/1.png"));
    }
    lbl->setScaledContents(true);
    int width = commandArgs.at(1).toInt();
    int height = commandArgs.at(2).toInt();
    int x = commandArgs.at(3).toInt() - width/2;
    int y = commandArgs.at(4).toInt() - height/2;
    lbl->setGeometry(x,y,width,height);
}

void MainWindow::getBuildingInfo(QString command)
{
    QStringList commandArgs = command.split(" ");
}

void MainWindow::getUnitInfo(QString command)
{
    QStringList commandArgs = command.split(" ");
}

void MainWindow::getPlayerInfo(QString command)
{
    QStringList commandArgs = command.split(" ");
}

void MainWindow::createBuilding(QString command)
{
    QStringList commandArgs = command.split(" ");
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::readyRead, this, &MainWindow::dataReceived);
    connect(socket, &QTcpSocket::disconnected, this, &MainWindow::serverDisconnected);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateGameState(QString srvrMsg)
{
    QStringList commands = srvrMsg.split("%%");
    for (int i = 0; i < commands.size(); ++i) {
        QStringList commandargs = commands.at(i).split(" ");
        int commandType = commandargs.at(0).toInt();
        switch (commandType) {
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

void MainWindow::on_btnConnect_clicked()
{
    // Decide to connect to supplied IP or to localhost.
    if (this->ui->lnIPAddr->text().size() == 0)
    {
        QMessageBox::information(this, "Note", "Start the server and then close this window.");
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

    disConExpected = false;
    ui->btnConnect->setEnabled(false);

    // This window should contain a "start" button and a "disconnect" button.
    // If the start button is selected, the game window should be launched.
    // If the disconnect is selected, this window and the socket should be closed.
    QDialog *GameInitWin = new QDialog();
    GameInitWin->show();
    GameInitWin->activateWindow(); // Do we need this?
}

void MainWindow::on_btnHelp_clicked()
{
    QMessageBox::information(this, "Help", "Press Start to start a game. Enter an IP address in the text box to connect to a remote game, or leave blank to create a local server.");
}

void MainWindow::on_btnExit_clicked()
{
    disConExpected = true;
    this->close();
}

void MainWindow::dataReceived()
{
    QTcpSocket *sock = dynamic_cast<QTcpSocket*>(sender());
    while (sock->canReadLine()) {
        QString str = sock->readLine();
        updateGameState(str);
    }
}

void MainWindow::serverDisconnected()
{
    socket->close();
    ui->btnConnect->setEnabled(true);
    if (!disConExpected)
    {
        QMessageBox::critical(this, "Disconnect", "Connection to server lost!");
        disConExpected = true; // Is this necessary to ensure future good behavior?
    }
}
