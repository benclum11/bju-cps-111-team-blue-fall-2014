#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QString>
#include <QMainWindow>
#include <QTcpSocket>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QString netAddress;
    bool disConExpected;
    void networkDisconect();
    
private slots:
    void on_btnExit_clicked();
    void on_btnConnect_clicked();
    void on_btnHelp_clicked();
    void dataReceived();
    void serverDisconnected();
    void launchLobby();

private:
    Ui::MainWindow *ui;

    QTcpSocket *socket;
};

#endif // MAINWINDOW_H
