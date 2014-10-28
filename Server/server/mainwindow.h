#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QTcpServer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void addToLog(QString msg);

private slots:

    void timerHit();
    void clientConnected();
    void clientDisconnected();
    void dataRecieved();
    
private:
    Ui::MainWindow *ui;

    QTimer* timer;

    QTcpServer* server;

    bool worldCreated;
    bool paused;

    void processClientMessage(QString&);
    void updateClient();
};

#endif // MAINWINDOW_H
