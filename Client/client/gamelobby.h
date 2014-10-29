#ifndef GAMELOBBY_H
#define GAMELOBBY_H

#include <QDialog>
#include <mainwindow.h>
#include <QTcpSocket>

namespace Ui {
class gameLobby;
}

class gameLobby : public QDialog
{
    Q_OBJECT

    Ui::gameLobby *ui;
    QTcpSocket* socket;
    QWidget* parent;
    bool unexpected;

public:
    explicit gameLobby(QWidget *parent = 0, QTcpSocket* = 0);
    ~gameLobby();

private slots:
    void on_btnStart_clicked();

    void on_btnDisconnect_clicked();

    void serverDisconnected();
};

#endif // GAMELOBBY_H
