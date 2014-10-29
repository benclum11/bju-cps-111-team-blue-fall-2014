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
    QString serverMsg = "5\n";
    socket->write(serverMsg.toLocal8Bit());
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
    QTcpSocket *sock = dynamic_cast<QTcpSocket*>(sender());
    while (sock->canReadLine()) {
        initMsg = sock->readLine();
    }
}
