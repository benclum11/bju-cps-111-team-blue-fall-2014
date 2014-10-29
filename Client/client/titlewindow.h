#ifndef TitleWindow_H
#define TitleWindow_H

#include <QString>
#include <QMainWindow>
#include <QTcpSocket>

namespace Ui {
class TitleWindow;
}

class TitleWindow : public QMainWindow
{
    Q_OBJECT

    Ui::TitleWindow *ui;

    QTcpSocket *socket;

    void getTileInfo(QString);
    void getBuildingInfo(QString);
    void getUnitInfo(QString);
    void getPlayerInfo(QString);
    void createBuilding(QString);
    
public:
    explicit TitleWindow(QWidget *parent = 0);
    ~TitleWindow();
    QString netAddress;

    void updateGameState(QString);
    void networkDisconect();
    
private slots:
    void on_btnExit_clicked();
    void on_btnConnect_clicked();
    void on_btnHelp_clicked();
    void dataReceived();
    void launchLobby();

};

#endif // TitleWindow_H
