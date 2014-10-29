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

    Ui::MainWindow *ui;

    QTcpSocket *socket;

    void getTileInfo(QString);
    void getBuildingInfo(QString);
    void getUnitInfo(QString);
    void getPlayerInfo(QString);
    void createBuilding(QString);
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QString netAddress;
    bool disConExpected;

    void updateGameState(QString);
    
private slots:
    void on_btnExit_clicked();
    void on_btnConnect_clicked();
    void on_btnHelp_clicked();
    void dataReceived();
    void serverDisconnected();

};

#endif // MAINWINDOW_H
