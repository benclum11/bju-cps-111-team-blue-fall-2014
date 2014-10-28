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
    
private slots:
    void on_btnExit_clicked();
    void on_btnStart_clicked();
    void on_btnHelp_clicked();
    void dataReceived();
    void serverDisconnected();

private:
    Ui::MainWindow *ui;

    QTcpSocket *socket;
};

#endif // MAINWINDOW_H
