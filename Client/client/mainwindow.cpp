#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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

}

void MainWindow::on_btnHelp_clicked()
{
    QMessageBox::information(this, "Help", "Press Start to start a game. Enter an IP address in the text box to connect to a remote game, otherwise leave blank. Press Exit to quit.");
}
