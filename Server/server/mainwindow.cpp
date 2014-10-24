#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "world.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timer = new QTimer(this);
    timer->setInterval(20);
    connect(timer, &QTimer::timeout, this, &MainWindow::timerHit);

    timer->start();
}

void MainWindow::timerHit() {
    World::Instance();
}

MainWindow::~MainWindow()
{
    delete ui;
}
