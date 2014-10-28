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

void MainWindow::on_btnExit_clicked()
{
    this->close();
}

void MainWindow::on_btnStart_clicked()
{
    //this->netAddress = ui->lnIPAddr->text();
    if (this->ui->lnIPAddr->text().size() == 0)
    {
        socket->connectToHost("localhost", 5000); //Change port number.
    }
    else
    {
    socket->connectToHost(ui->lnIPAddr->text(), 5000); //The port needs to be cnahged to whatever port we are actually using.
    }

    if (!socket->waitForConnected())
    {
        QMessageBox::critical(this, "Error", "Unable to connect to server.");
        return;
    }
}

void MainWindow::on_btnHelp_clicked()
{
    QMessageBox::information(this, "Help", "Press Start to start a game. Enter an IP address in the text box to connect to a remote game, otherwise leave blank. Press Exit to quit.");
}

void MainWindow::dataReceived()
{

}

void MainWindow::serverDisconnected()
{

}
