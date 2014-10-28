#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>

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

void MainWindow::on_btnConnect_clicked()
{
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

    disConExpected = false;
    ui->btnConnect->setEnabled(false);

    QDialog *GameInitWin = new QDialog();
    GameInitWin->show();
    //GameInitWin->activateWindow(); // Do we need this?
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

}

void MainWindow::serverDisconnected()
{
    socket->close();
    ui->btnConnect->setEnabled(true);
    if (!disConExpected)
    {
        QMessageBox::information(this, "Disconnect", "Connection to server lost!");
        disConExpected = true; // Is this necessary to ensure future good behavior?
    }
}
