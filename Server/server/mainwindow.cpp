#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "world.h"
#include <QTcpServer>
#include <QTcpSocket>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timer = new QTimer(this);
    timer->setInterval(20);
    connect(timer, &QTimer::timeout, this, &MainWindow::timerHit);
}

void MainWindow::timerHit()
{

}

MainWindow::~MainWindow()
{
    delete ui;
}
