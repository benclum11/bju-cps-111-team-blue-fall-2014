#include <mainwindow.h>
#include "gamelobby.h"
#include "ui_gamelobby.h"

gameLobby::gameLobby(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gameLobby)
{
    ui->setupUi(this);
}

gameLobby::~gameLobby()
{
    delete ui;
}

void gameLobby::on_btnStart_clicked()
{

}

void gameLobby::on_btnDisconnect_clicked()
{
    this->close();
}
