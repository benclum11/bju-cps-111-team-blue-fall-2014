#include "ui_gamewindow.h"
#include "gamewindow.h"
#include "displaybuilding.h"
#include <units.h>
#include <QLabel>
#include <QPixmap>
#include <QString>
#include <QDebug>

GameWindow::GameWindow(QString& initMsg, QWidget* parent, QTcpSocket* socket) :
    QDialog(parent), parent(parent), ui(new Ui::GameWindow),
    socket(socket), unexpected(true), windowSized(false)
{
    ui->setupUi(this);
    gameDisplay = new QWidget(this);
    HighlightedLabel *label = new HighlightedLabel(gameDisplay);

    actionDisplay = new QWidget(this);
    HighlightedLabel *towerLabel = new HighlightedLabel(actionDisplay);

    updateGameState(initMsg);
    parent->hide();

    connect(socket, &QTcpSocket::readyRead, this, &GameWindow::dataReceived);
    connect(socket, &QTcpSocket::disconnected, this, &GameWindow::serverDisconnected);

    //button is created that can be shown and hidden that will do different things (text can be set and changed, etc)
    btn = new QPushButton("Create Tower", this->actionDisplay);
    connect(btn, &QPushButton::clicked, this, &GameWindow::on_btn_clicked);
    btn->setGeometry(actionDisplay->width() - 100, actionDisplay->height()- 26 ,100, 25);
    btn->raise();
    btn->show();

    //button to save game
    saveGame = new QPushButton("Save Game", this);
    connect(saveGame, &QPushButton::clicked, this, &GameWindow::on_saveGame_clicked);
    saveGame->setGeometry(this->width() - 265, this->height()- 40 ,100, 25);
    saveGame->raise();
    saveGame->show();

    filename = new QTextEdit(this);
    filename->setGeometry(this->width() - 150, this->height()- 40 ,100, 25);
    filename->raise();
    filename->show();

    //3 labels that can be selected to choose which tower to create
    tower1 = new ChooseTower(actionDisplay, 1);
    tower1->make(":/Resources/Buildings/1.png", 50, 50, 50, 50, true);

    tower2 = new ChooseTower(actionDisplay, 2);
    tower2->make(":/Resources/Buildings/2.png", 110, 50, 50, 50, true);

    tower3 = new ChooseTower(actionDisplay, 3);
    tower3->make(":/Resources/Buildings/3.png", 170, 50, 50, 50, true);

    btnUnits = new QPushButton("Create Unit", this->actionDisplay);
    btnUnits->setGeometry(actionDisplay->width() - 215, actionDisplay->height() -26, 100, 25);
    btnUnits->setObjectName(QString::fromUtf8("btnUnits"));
    btnUnits->raise();
    btnUnits->show();
    connect(btnUnits, &QPushButton::clicked, this, &GameWindow::on_btnUnits_clicked);
}

BuildableLabel* GameWindow::getClickedLabel()
{
    for (QObject *obj : gameDisplay->children())
    {
        BuildableLabel *lbl = dynamic_cast<BuildableLabel*>(obj);
        if (lbl != nullptr) {
            if (lbl->getClicked()) {
                return lbl;
            }
        }
    }
    return NULL;
}

ChooseTower* GameWindow::getTowerChosen()
{
    for (QObject *obj : actionDisplay->children())
    {
        ChooseTower *lbl = dynamic_cast<ChooseTower*>(obj);
        if (lbl != nullptr) {
            if (lbl->getClicked()) {
                return lbl;
            }
        }
    }
    return NULL;
}

GameWindow::~GameWindow()
{
    delete ui;
    parent->close();
}

void GameWindow::serverDisconnected()
{
    this->close();
}

void GameWindow::dataReceived()
{
    QTcpSocket *sock = dynamic_cast<QTcpSocket*>(sender());
    while (sock->canReadLine()) {
        QString str = sock->readLine();
        updateGameState(str);
    }
}


void GameWindow::on_btn_clicked() {
    QString serverMsg = "";
    ChooseTower* tower = getTowerChosen();
    if (tower != nullptr) {
        if(btn->text() == "Create Tower") {
            BuildableLabel* lbl = getClickedLabel();
            if (lbl != NULL) {
                if (lbl->getClientTeam() == team) {
                    if (tower->getTowerNumber() == 1) {
                        serverMsg = QString("1") + QString(" 1_1_1 ") + QString::number(lbl->getXCenter()) + " " + QString::number(lbl->getYCenter()) + " \n";
                    } else if (tower->getTowerNumber() == 2) {
                        serverMsg = QString("1") + QString(" 1_2_1 ") + QString::number(lbl->getXCenter()) + " " + QString::number(lbl->getYCenter()) + " \n";
                    } else if (tower->getTowerNumber() == 3) {
                        serverMsg = QString("1") + QString(" 1_3_1 ") + QString::number(lbl->getXCenter()) + " " + QString::number(lbl->getYCenter()) + " \n";
                    }
                }
                socket->write(serverMsg.toLocal8Bit());
                qDebug() << serverMsg << endl;
            }
        }
    }    
}

void GameWindow::on_btnUnits_clicked()
{

    //units* unit = new units("2_1_1", 175, 25, 2, gameDisplay);
    QString unitCreate = QString("3") + " 3_1_1 " + "1\n";
    socket->write(unitCreate.toLocal8Bit());
}

void GameWindow::on_saveGame_clicked()
{
    QString serverMsg;
    if ((filename->toPlainText() == "") || (filename->toPlainText() == " ")) {
        QMessageBox::critical(this, "Error!", "Please Enter a Vaid Filename");
        return;
    } else {
        serverMsg = QString("6 ") + filename->toPlainText() + "\n";
        socket->write(serverMsg.toLocal8Bit());
        QMessageBox::warning(this, "Saved", "Your game was saved");
    }
}

void GameWindow::on_btnExitGame_clicked()
{
    this->close();
}

void GameWindow::getTileInfo(QString command)
{
    QStringList commandArgs = command.split(" ");
    if (!windowSized) {
        int gameWidth = commandArgs.at(1).toInt() * commandArgs.at(3).toInt();
        int gameHeight = commandArgs.at(2).toInt() * commandArgs.at(4).toInt();
        resize(gameWidth + 500, gameHeight + 300);
        setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        gameDisplay->setGeometry(50, 250, gameWidth,gameHeight);
        gameDisplay->setMinimumWidth(gameWidth);
        gameDisplay->setMaximumWidth(gameWidth);
        gameDisplay->setMinimumHeight(gameHeight);
        gameDisplay->setMaximumHeight(gameHeight);
        lblWidth = commandArgs.at(3).toInt();
        lblHeight = commandArgs.at(4).toInt();
        gameDisplay->show();

        actionDisplay->setGeometry(gameWidth + 100, 50, 350, gameHeight + 200);
        actionDisplay->setMinimumWidth(350);
        actionDisplay->setMinimumHeight(gameHeight + 200);
        actionDisplay->setMaximumWidth(350);
        actionDisplay->setMaximumHeight(gameHeight + 200);

        actionDisplay->show();
    }
    if (windowSized) {
        QLabel* lbl;
        if (commandArgs.at(5) == "0") {
            lbl = new QLabel(gameDisplay);
            lbl->setPixmap(QPixmap("://Resources/Tiles/0.png"));
            lbl->setScaledContents(true);
            int x = commandArgs.at(3).toInt() - lblWidth/2;
            int y = commandArgs.at(4).toInt() - lblHeight/2;
            lbl->setGeometry(x,y,lblWidth,lblHeight);
            lbl->show();
        } else {
            BuildableLabel *lbl = new BuildableLabel(gameDisplay, commandArgs.at(6).toInt());
            lbl->setPixmap(QPixmap("://Resources/Tiles/1.png"));
            lbl->setScaledContents(true);
            int x = commandArgs.at(3).toInt() - lblWidth/2;
            int y = commandArgs.at(4).toInt() - lblHeight/2;
            lbl->setGeometry(x,y,lblWidth,lblHeight);
            lbl->show();
        }
    }
    windowSized = true;
}

void GameWindow::getBuildingInfo(QString command)
{
    QStringList commandArgs = command.split(" ");

    QStringList unlocks = commandArgs.at(7).split(",");
    Stats stat(commandArgs.at(1), commandArgs.at(2).toInt(), commandArgs.at(3).toInt(),
               commandArgs.at(4).toInt(), commandArgs.at(5).toInt(), commandArgs.at(6).toInt(), unlocks);
    stats.push_back(stat);
}

void GameWindow::getUnitInfo(QString command)
{
    QStringList commandArgs = command.split(" ");

    Stats stat(commandArgs.at(1), commandArgs.at(4).toInt(), commandArgs.at(3).toInt(),
               commandArgs.at(2).toInt(), commandArgs.at(5).toInt());
    stats.push_back(stat);
}

void GameWindow::getPlayerInfo(QString command)
{
    QStringList commandArgs = command.split(" ");
}

void GameWindow::createBuilding(QString command)
{
    QStringList commandArgs = command.split(" ");

    QStringList unlocks = commandArgs.at(10).split(",");
    DisplayBuilding* build = new DisplayBuilding(gameDisplay, getStatsByType(commandArgs.at(3)), commandArgs.at(5).toInt(),commandArgs.at(6).toInt(),
                          commandArgs.at(7).toInt(), commandArgs.at(8).toInt(), commandArgs.at(9).toInt(), unlocks, commandArgs.at(4).toInt());

    build->setGeometry(commandArgs.at(1).toInt() - lblWidth/2, commandArgs.at(2).toInt() - lblHeight/2, lblWidth, lblHeight);
    build->setScaledContents(true);
    build->raise();
    build->raise();
    build->show();
}

void GameWindow::getPlayerHealth(QString command)
{
    QStringList commandArgs = command.split(" ");

    bool ok;
    int team, health;
    team = commandArgs.at(0).toInt(&ok, 10);
    if (ok) health = commandArgs.at(1).toInt(&ok, 10);

    if (ok)
    {

    } else
    {

    }
}

void GameWindow::getPlayerMoney(QString command)
{
    QStringList commandArgs = command.split(" ");

/*
    bool ok;
    int team, money;
    team = commandArgs.at(0).toInt(&ok, 10);
    if (ok) money = commandArgs.at(1).toInt(&ok, 10);

    if (ok)
    {

    } else
    {

    }
*/
}

void GameWindow::getPlayerHealthMoney(QString command)
{
    QStringList commandArgs = command.split(" ");
}

void GameWindow::getBuildingUpgrade(QString command)
{
    QStringList commandArgs = command.split(" ");

    bool ok;
    int x, y, type, nxtLvlAttack, nxtLvlSpeed, nxtLvlRange, nxtLvlProd, nxtLvlCost;
    x = commandArgs.at(0).toInt(&ok, 10);
    if (ok) y = commandArgs.at(1).toInt(&ok, 10);
    if (ok) type = commandArgs.at(2).toInt(&ok, 10);
    if (ok) nxtLvlAttack = commandArgs.at(3).toInt(&ok, 10);
    if (ok) nxtLvlSpeed = commandArgs.at(4).toInt(&ok, 10);
    if (ok) nxtLvlRange = commandArgs.at(5).toInt(&ok, 10);
    if (ok) nxtLvlProd = commandArgs.at(6).toInt(&ok, 10);
    if (ok) nxtLvlCost = commandArgs.at(7).toInt(&ok, 10);
    QString unlock = commandArgs.at(8);

    if (ok)
    {

    } else
    {

    }
}

void GameWindow::getBuildingDeath(QString command)
{
    QStringList commandArgs = command.split(" ");

    bool ok;
    int x, y;
    x = commandArgs.at(0).toInt(&ok, 10);
    if (ok) y = commandArgs.at(1).toInt(&ok, 10);

    if (ok)
    {

    } else
    {

    }
}

void GameWindow::getUnitCreation(QString command)
{
        QStringList commandArgs = command.split(" ");
        bool ok;
        QString type;
        int team, health, x, y, facing;

        type = commandArgs.at(2);
        //team = commandArgs.at(1).toInt(&ok, 10);
        //if (ok) health = commandArgs.at(2).toInt(&ok, 10);
        if (ok) x = commandArgs.at(3).toInt(&ok, 10);
        if (ok) y = commandArgs.at(4).toInt(&ok, 10);
        if (ok) facing = commandArgs.at(5).toInt(&ok, 10);

        if (ok)
        {
            units* unit = new units(type, x, y, facing, gameDisplay);

        } else
        {
            //what happens if it fails?
        }
}

void GameWindow::getUnitMove(QString command)
{
    QStringList commandArgs = command.split(" ");

    bool ok;
    int id = commandArgs.at(0).toInt(&ok, 10);
    int x, y;
    if (ok) x = commandArgs.at(1).toInt(&ok, 10);
    if (ok) y = commandArgs.at(2).toInt(&ok, 10);

    if (ok)
    {
        //call move unit
    } else
    {
        //what happens if it fails?
    }
}

void GameWindow::getUnitMoveTurn(QString command)
{
    QStringList commandArgs = command.split(" ");

    bool ok;
    int id, x, y, facing;

    id = commandArgs.at(0).toInt(&ok, 10);
    if (ok) x = commandArgs.at(1).toInt(&ok, 10);
    if (ok) y = commandArgs.at(2).toInt(&ok, 10);
    if (ok) facing = commandArgs.at(3).toInt(&ok, 10);

    if (ok)
    {

    } else
    {

    }
}

void GameWindow::getUnitMoveHealth(QString command)
{
    QStringList commandArgs = command.split(" ");

    bool ok;
    int id = commandArgs.at(0).toInt(&ok, 10);
    int x, y, health;
    if (ok) health = commandArgs.at(1).toInt(&ok, 10);
    if (ok) x = commandArgs.at(2).toInt(&ok, 10);
    if (ok) y = commandArgs.at(3).toInt(&ok, 10);

    if (ok)
    {
        //call unit commands
    } else
    {
        //what happens if it fails?
    }
}

void GameWindow::getUnitMoveTurnHealth(QString command)
{
    QStringList commandArgs = command.split(" ");

    bool ok;
    int id, health, x, y, facing;

    id = commandArgs.at(0).toInt(&ok, 10);
    if (ok) health = commandArgs.at(1).toInt(&ok, 10);
    if (ok) x = commandArgs.at(2).toInt(&ok, 10);
    if (ok) y = commandArgs.at(3).toInt(&ok, 10);
    if (ok) facing = commandArgs.at(4).toInt(&ok, 10);

    if (ok)
    {
        //call unit commands
    } else
    {
        //what happens if it fails?
    }
}

void GameWindow::getUnitDeath(QString command)
{
    bool ok;
    int id = command.toInt(&ok, 10);

    if (ok)
    {
        //call unit destroy
    } else
    {

    }
}

void GameWindow::getBulletInfo(QString command)
{
    QStringList commandArgs = command.split(" ");

    bool ok;
    int x, y;
    x = commandArgs.at(0).toInt(&ok, 10);
    if (ok) y = commandArgs.at(1).toInt(&ok, 10);

    if (ok)
    {

    } else
    {

    }
}

void GameWindow::doGamePause()
{

}

Stats GameWindow::getStatsByType(QString type)
{
    for(Stats info : stats) {
        if(info.getType() == type) { return info; }
    }
}

void GameWindow::updateGameState(QString srvrMsg)
{
    QStringList commands = srvrMsg.split("%%");
    commands.pop_back();
    for (int i = 0; i < commands.size(); ++i) {
        QStringList commandargs = commands.at(i).split(" ");
        int commandType = commandargs.at(0).toInt();
        switch (commandType) {
        case 0:
            team = commands.at(i).split(" ").at(1).toInt();
            BuildableLabel::setClientTeam(team);
            break;
        case 1:
            getTileInfo(commands.at(i));
            break;
        case 2:
            getBuildingInfo(commands.at(i));
            break;
        case 3:
            getUnitInfo(commands.at(i));
            break;
        case 11:
            getPlayerInfo(commands.at(i));
            break;
        case 14:
            getPlayerHealth(commands.at(i));
            break;
        case 16:
            getPlayerMoney(commands.at(i));
            break;
        case 17:
            getPlayerHealthMoney(commands.at(i));
            break;
        case 21:
            createBuilding(commands.at(i));
            break;
        case 28:
            getBuildingUpgrade(commands.at(i));
            break;
        case 20:
            getBuildingDeath(commands.at(i));
            break;
        case 31:
            getUnitCreation(commands.at(i));
            break;
        case 32:
            getUnitMove(commands.at(i));
            break;
        case 33:
            getUnitMoveTurn(commands.at(i));
            break;
        case 34:
            getUnitMoveHealth(commands.at(i));
            break;
        case 35:
            getUnitMoveTurnHealth(commands.at(i));
            break;
        case 30:
            getUnitDeath(commands.at(i));
            break;
        case 4:
            getBulletInfo(commands.at(i));
            break;
        case 5:
            doGamePause();
            break;
        default:
            break;
        }
    }
}
