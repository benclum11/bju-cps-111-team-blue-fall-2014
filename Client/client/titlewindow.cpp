#include "titlewindow.h"
#include "ui_titlewindow.h"
#include <QMessageBox>
#include <QString>
#include <QPixmap>
#include <gamelobby.h>
#include "helpwindow.h"

TitleWindow::TitleWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TitleWindow)
{
    ui->setupUi(this);

    socket = new QTcpSocket(this);
}

TitleWindow::~TitleWindow()
{
    delete ui;
}

void TitleWindow::on_btnConnect_clicked()
{
    // Decide to connect to supplied IP or to localhost.
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

    launchLobby();
}

void TitleWindow::on_btnHelp_clicked()
{
    helpWindow help;
    help.setModal(true);
    help.exec();
}

void TitleWindow::on_btnExit_clicked()
{
    this->close();
}

// Disables connect button and opens the game lobby window
void TitleWindow::launchLobby()
{
    gameLobby lobby(this, socket);
    lobby.setModal(true);
    lobby.exec();
}
