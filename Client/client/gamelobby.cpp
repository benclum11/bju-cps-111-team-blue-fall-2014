#include <titlewindow.h>
#include "gamelobby.h"
#include "ui_gamelobby.h"
#include <QMessageBox>

gameLobby::gameLobby(QWidget* parent, QTcpSocket* socket) :
     QDialog(parent), ui(new Ui::gameLobby), socket(socket),
     parent(parent), unexpected(true)
{
    ui->setupUi(this);
    parent->hide();
    connect(socket, &QTcpSocket::disconnected, this, &gameLobby::serverDisconnected);
}

gameLobby::~gameLobby()
{
    delete ui;
}

void gameLobby::on_btnStart_clicked()
{
    QString serverMsg = "5";
    socket->write(serverMsg.toLocal8Bit());
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
