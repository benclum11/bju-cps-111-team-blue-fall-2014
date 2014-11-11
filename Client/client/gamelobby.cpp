//This file contains code for the initial game lobby window. The lobby serves as a starting point for a networked game.

#include "gamelobby.h"
#include "ui_gamelobby.h"
#include "gamewindow.h"
#include <QMessageBox>

gameLobby::gameLobby(QWidget* parent, QTcpSocket* socket) :
     QDialog(parent), ui(new Ui::gameLobby), socket(socket),
     parent(parent), unexpected(true), initMsg("")
{
    ui->setupUi(this);
    parent->hide();
    connect(socket, &QTcpSocket::readyRead, this, &gameLobby::dataReceived);
    connect(socket, &QTcpSocket::disconnected, this, &gameLobby::serverDisconnected);
}

gameLobby::~gameLobby()
{
    delete ui;
}

void gameLobby::on_btnStart_clicked()
{
    GameWindow game(initMsg, this, socket);
    game.exec();
}

void gameLobby::on_btnDisconnect_clicked()
{
    unexpected = false;
    socket->close();
}

void gameLobby::serverDisconnected()
{
    if(unexpected)
    {
        socket->close();
        QMessageBox::critical(this, "Disconnect", "Connection to server lost!");
    }
    parent->show();
    this->close();
}

void gameLobby::dataReceived()
{
    if (initMsg == "")
    {
        QTcpSocket *sock = dynamic_cast<QTcpSocket*>(sender());
        while (sock->canReadLine()) {
            initMsg = sock->readLine();
        }
    }
}

void gameLobby::closeEvent(QCloseEvent *event)
{
    QString teamCommand = initMsg.split("%%").at(0);
    QString team = teamCommand.split(" ").at(1);
    QString closeMessage = "9 " + team + "\n";
    socket->write(closeMessage.toLocal8Bit());
    unexpected = false;
    socket->close();
    event->accept();
}

void gameLobby::on_loadBtn_clicked()
{
    if (ui->loadBox->text() == "") {
        QMessageBox::critical(this, "Error!", "Please Enter A File Name");
        return;
    } else if (ui->loadBox->text().contains(".txt")) {
        QMessageBox::critical(this, "Error!", "Please Do Not Include The File Extension");
        return;
    } else {
        QString serverMsg = QString("7 ") + ui->loadBox->text() + "\n";
        socket->write(serverMsg.toLocal8Bit());
        GameWindow game(initMsg, this, socket);
        game.exec();
    }
}
