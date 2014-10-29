#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "world.h"
#include <QTcpSocket>
#include <QMessageBox>
#include <QDateTime>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    paused = true;
    ui->setupUi(this);

    timer = new QTimer(this);
    timer->setInterval(20);
    connect(timer, &QTimer::timeout, this, &MainWindow::timerHit);

    server = new QTcpServer(this);
    if(!server->listen(QHostAddress::Any, 10000)) {
        QMessageBox::critical(this,"Error","Cannot start socket. Is another instance already running?");
        exit(1);
    }
    connect(server, &QTcpServer::newConnection, this, &MainWindow::clientConnected);

}

void MainWindow::timerHit()
{
    for(QObject* obj : server->children()) {
        QTcpSocket *anotherSock = dynamic_cast<QTcpSocket*>(obj);
        if (anotherSock != NULL)
            updateClient();
    }
}

void MainWindow::clientConnected()
{
    QTcpSocket* sock = server->nextPendingConnection();
    connect(sock, &QTcpSocket::disconnected, this, &MainWindow::clientDisconnected);
    connect(sock, &QTcpSocket::readyRead, this, &MainWindow::dataRecieved);
    QString clientMsg = (World::Instance()->getSendToClient()) + "\n";
    sock->write(clientMsg.toLocal8Bit());
    addToLog("Client connected.");
    if(false)
    {
        timer->start();
        paused = false;
        clientMsg = "5\n";
        sock->write(clientMsg.toLocal8Bit());
    }
}

void MainWindow::clientDisconnected()
{
    QTcpSocket* sock = dynamic_cast<QTcpSocket*>(sender());
    sock->deleteLater();
    addToLog("Client disconnected.");

    //might wanna remove this after some debugging......
    World::Reset();
}

void MainWindow::dataRecieved()
{
    QTcpSocket* sock = dynamic_cast<QTcpSocket*>(sender());
    while(sock->canReadLine()) {
        QString line = sock->readLine();
        World::Instance();
        processClientMessage(line, sock);
    }
}

void MainWindow::processClientMessage(QString& message, QTcpSocket* sock)
{
    QStringList data = message.split("");
    QString command = data.at(0);
    if(command == "5") {
        if (paused) {
            timer->start();
            paused = false;
            QString clientMsg = "5";
            sock->write(clientMsg.toLocal8Bit());
        } else {
            timer->stop();
            paused = true;
            QString clientMsg = "5";
            sock->write(clientMsg.toLocal8Bit());
        }
    } else if(command == "6") {
        World::Instance()->save(data.at(1));
    } else if (command == "7") {
        World::Instance()->load(data.at(1));
    } else if (command == "1") {
        World::Instance()->buyTower(data);
    } else if (command =="3") {
        World::Instance()->buyUnit(data);
    } else if (command == "0") {
        World::Instance()->destroy(data);
    } else if (command == "8") {
        World::Instance()->upgrade(data);
    }
}

void MainWindow::updateClient()
{

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addToLog(QString msg)
{
    QDateTime now = QDateTime::currentDateTime();
    ui->txtLog->appendPlainText(now.toString("hh:mm:ss") + " " + msg);
}
