#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>
#include "helpwindow.h"
#include <gamelobby.h>

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

// Gracefully closes connection and re-enables connect button
void MainWindow::networkDisconect()
{
    disConExpected = true;
    socket->close();
    ui->btnConnect->setEnabled(true);
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
    disConExpected = true;
    this->close();
}

void MainWindow::dataReceived()
{

}

void MainWindow::serverDisconnected()
{
    socket->close();
    ui->btnConnect->setEnabled(true);
    if (!disConExpected)
    {
        QMessageBox::critical(this, "Disconnect", "Connection to server lost!");
        //disConExpected = true; // Is this necessary to ensure future good behavior?
    }
}

// Disables connect button and opens the game lobby window
void MainWindow::launchLobby()
{
    disConExpected = false;
    ui->btnConnect->setEnabled(false);

    gameLobby lobby(this);
    lobby.setModal(true);
    lobby.exec();
    networkDisconect();
}
