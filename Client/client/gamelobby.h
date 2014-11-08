#ifndef GAMELOBBY_H
#define GAMELOBBY_H

#include <QDialog>
#include <QTcpSocket>
#include <QCloseEvent>

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
    QString initMsg;

public:
    explicit gameLobby(QWidget *parent = 0, QTcpSocket* = 0);
    ~gameLobby();

private slots:
    void on_btnStart_clicked();

    void on_btnDisconnect_clicked();

    void serverDisconnected();

    void dataReceived();

    void closeEvent(QCloseEvent*);
    void on_loadBtn_clicked();
};

#endif // GAMELOBBY_H
