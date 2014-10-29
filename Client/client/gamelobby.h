#ifndef GAMELOBBY_H
#define GAMELOBBY_H

#include <QDialog>
#include <mainwindow.h>

namespace Ui {
class gameLobby;
}

class gameLobby : public QDialog
{
    Q_OBJECT

public:
    explicit gameLobby(QWidget *parent = 0);
    ~gameLobby();

private slots:
    void on_btnStart_clicked();

    void on_btnDisconnect_clicked();

private:
    Ui::gameLobby *ui;
};

#endif // GAMELOBBY_H
