//This file contains code for the game display. Most of the client events happen here.

#include "ui_gamewindow.h"
#include "gamewindow.h"
#include "displaybuilding.h"
#include "units.h"
#include <QLabel>
#include <QPixmap>
#include <QString>
#include <QDebug>

GameWindow::GameWindow(QString& initMsg, QWidget* parent, QTcpSocket* socket) :
    QDialog(parent), parent(parent), ui(new Ui::GameWindow),
    socket(socket), unexpected(true), windowSized(false)
{
    ui->setupUi(this);

    //Display for game events.
    gameDisplay = new QWidget(this);
    HighlightedLabel *label = new HighlightedLabel(gameDisplay); //used to select items in the game display

    //Display for buttons and selections.
    actionDisplay = new QWidget(this);
    HighlightedLabel *towerLabel = new HighlightedLabel(actionDisplay); //used to select items in the action display

    updateGameState(initMsg);
    parent->hide();

    connect(socket, &QTcpSocket::readyRead, this, &GameWindow::dataReceived);
    connect(socket, &QTcpSocket::disconnected, this, &GameWindow::serverDisconnected);

    createLabelsandButtons();
}

// Creates labels and buttons for the game state
void GameWindow::createLabelsandButtons()
{
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

    //Textbox for saved game filename.
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

    //3 labels to choose which unit to create
    unit1 = new ChooseTower(actionDisplay, 4);
    unit1->make(":/Resources/Units/0/1.png", 50, 110, 50, 50, true);
    unit1->setEnabled(false);

    unit2 = new ChooseTower(actionDisplay, 5);
    unit2->make(":/Resources/Units/1/1.png", 110, 110, 50, 50, true);

    unit3 = new ChooseTower(actionDisplay, 6);
    unit3->make(":/Resources/Units/2/2.png", 170, 110, 50, 50, true);

    //button to create units
    btnUnits = new QPushButton("Create Unit", this->actionDisplay);
    btnUnits->setGeometry(actionDisplay->width() - 215, actionDisplay->height() -26, 100, 25);
    btnUnits->setObjectName(QString::fromUtf8("btnUnits"));
    btnUnits->raise();
    btnUnits->show();
    connect(btnUnits, &QPushButton::clicked, this, &GameWindow::on_btnUnits_clicked);

    //label that displays the users money
    money = new QLabel(this->actionDisplay);
    money->setGeometry(50,200,200,50);
    money->setText("Current Money: 100");
    money->raise();
    money->show();

    //label that displays the users health
    health = new QLabel(this->actionDisplay);
    health->setGeometry(50,250,200,50);
    health->setText("Current Health: 20");
    health->raise();
    health->show();

    //button to start the timer
    startBtn = new QPushButton("Start/Pause Timer", this);
    connect(startBtn, &QPushButton::clicked, this, &GameWindow::on_start_clicked);
    startBtn->setGeometry(5, 612, 150, 25);
    startBtn->raise();
    startBtn->show();
}

// Insert comment here
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

// Insert comment here
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

// Displays winning team and closes game.
void GameWindow::doGameOver(QString command)
{
     QStringList commandArgs = command.split(" ");

     int deadTeam = commandArgs.at(1).toInt();

     if (deadTeam == 1) {
          QMessageBox::critical(this, "GAME OVER", "Player 2 Wins!");
          this->close();
     }
     else if (deadTeam == 2) {
         QMessageBox::critical(this, "GAME OVER", "Player 1 Wins!");
         this->close();
     }

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

// Creates tower creation command and sends it to the server.
void GameWindow::on_btn_clicked() {
    QString serverMsg = "";
    ChooseTower* tower = getTowerChosen();
    if (tower != nullptr) {
        BuildableLabel* lbl = getClickedLabel();
        if (lbl != NULL) {
            if (BuildableLabel::getClientTeam() == lbl->getTeam()) {
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

// Creates a unit creation command and sends it to the server.
void GameWindow::on_btnUnits_clicked()
{
    QString unitCreate = "";
    ChooseTower* tower = getTowerChosen();
    if (tower != nullptr) {
        if (BuildableLabel::getClientTeam() == 1) {
            if (tower->getTowerNumber() == 4) {
                 unitCreate = QString("3") + " 2_0_1 " + "1 \n";
            } else if (tower->getTowerNumber() == 5) {
                 unitCreate = QString("3") + " 2_1_1 " + "1 \n";
            } else if (tower->getTowerNumber() == 6) {
                 unitCreate = QString("3") + " 2_2_1 " + "1 \n";
            }
            socket->write(unitCreate.toLocal8Bit());
        }
        if (BuildableLabel::getClientTeam() == 2) {
            if (tower->getTowerNumber() == 4) {
                 unitCreate = QString("3") + " 2_0_1 " + "2 \n";
            } else if (tower->getTowerNumber() == 5) {
                 unitCreate = QString("3") + " 2_1_1 " + "2 \n";
            } else if (tower->getTowerNumber() == 6) {
                 unitCreate = QString("3") + " 2_2_1 " + "2 \n";
            }
            socket->write(unitCreate.toLocal8Bit());
        }
    }
}

// Saves current game state to file.
void GameWindow::on_saveGame_clicked()
{
    QString serverMsg;
    if ((filename->toPlainText() == "") || (filename->toPlainText() == " ")) {
        QMessageBox::critical(this, "Error!", "Please Enter a Vaid Filename");
        return;
    } else if (filename->toPlainText().contains(".txt")) {
        QMessageBox::critical(this, "Error!", "Please Do Not Include The File Extension");
        return;
    } else {
        serverMsg = QString("6 ") + filename->toPlainText() + "\n";
        socket->write(serverMsg.toLocal8Bit());
        QMessageBox::warning(this, "Saved", "Your game was saved");
    }
}

// Sends signal to server to start game timer.
void GameWindow::on_start_clicked()
{
    QString serverMsg = "5 \n";
    socket->write(serverMsg.toLocal8Bit());
}

// Closes current game.
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

// Insert comment here
void GameWindow::getBuildingInfo(QString command)
{
    QStringList commandArgs = command.split(" ");

    QStringList unlocks = commandArgs.at(7).split(",");
    Stats stat(commandArgs.at(1), commandArgs.at(2).toInt(), commandArgs.at(3).toInt(),
               commandArgs.at(4).toInt(), commandArgs.at(5).toInt(), commandArgs.at(6).toInt(), unlocks);
    stats.push_back(stat);
}

// Insert comment here.
void GameWindow::getUnitInfo(QString command)
{
    QStringList commandArgs = command.split(" ");

    Stats stat(commandArgs.at(1), commandArgs.at(4).toInt(), commandArgs.at(3).toInt(),
               commandArgs.at(2).toInt(), commandArgs.at(5).toInt());
    stats.push_back(stat);
}

// Currently not implemented.
void GameWindow::getPlayerInfo(QString command)
{
    QStringList commandArgs = command.split(" ");
}


// Processes server command to create a new tower.
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


// Changes player health based on command from server.
void GameWindow::getPlayerHealth(QString command)
{
    QStringList commandArgs = command.split(" ");

    if (BuildableLabel::getClientTeam() == commandArgs.at(1).toInt()) {
        health->setText(QString("Current Health: ") + commandArgs.at(2));
    }
}

// Changes player money value based on command from server.
void GameWindow::getPlayerMoney(QString command)
{
    QStringList commandArgs = command.split(" ");

    if (BuildableLabel::getClientTeam() == commandArgs.at(1).toInt()) {
        money->setText(QString("Current Money: ") + commandArgs.at(2));
    }
}

// Depricated
void GameWindow::getPlayerHealthMoney(QString command)
{
//    QStringList commandArgs = command.split(" ");

//    if (BuildableLabel::getClientTeam() == commandArgs.at(1).toInt()) {
//        money->setText(QString("Current Money: ") + commandArgs.at(2));
//        health->setText(QString("Current Health: ") + commandArgs.at(3));
//    }
}

// Deprecated & not implemented. Processes server command to upgrade a building.
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

//Currently not implemented. Processes server command to delete a building. (Why do we even have this?)
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

// Processes server command to create a new unit.
void GameWindow::getUnitCreation(QString command)
{
        QStringList commandArgs = command.split(" ");
        bool ok;
        QString type;
        int id, team, health, x, y, facing;

        id = commandArgs.at(1).toInt();
        type = commandArgs.at(2);
        //team = commandArgs.at(1).toInt(&ok, 10);
        //if (ok) health = commandArgs.at(2).toInt(&ok, 10);
        if (ok) x = commandArgs.at(3).toInt(&ok, 10);
        if (ok) y = commandArgs.at(4).toInt(&ok, 10);
        if (ok) facing = commandArgs.at(5).toInt(&ok, 10);

        if (ok)
        {
            units* unit = new units(id, type, x, y, facing, gameDisplay);

        } else
        {
            //what happens if it fails?
        }
}

// Processes server command to move a unit.
void GameWindow::getUnitMove(QString command)
{
    QStringList commandArgs = command.split(" ");

    int id = commandArgs.at(1).toInt();
    int x, y;
    x = commandArgs.at(2).toInt();
    y = commandArgs.at(3).toInt();
    for (QObject *lbl : this->gameDisplay->children()) {
        units *unit = dynamic_cast<units*>(lbl);
        if (unit != nullptr) {
            if (unit->getID() == id) {
                unit->setXY(x,y);
            }
        }
    }
}

// Processes server command to move a unit and to change the image facing direction.
void GameWindow::getUnitMoveTurn(QString command)
{
    QStringList commandArgs = command.split(" ");

    bool ok;
    int id, x, y, facing;

    id = commandArgs.at(1).toInt(&ok, 10);
    if (ok) x = commandArgs.at(2).toInt(&ok, 10);
    if (ok) y = commandArgs.at(3).toInt(&ok, 10);
    if (ok) facing = commandArgs.at(4).toInt(&ok, 10);
    for (QObject *lbl : this->gameDisplay->children()) {
        units *unit = dynamic_cast<units*>(lbl);
        if (unit != nullptr) {
            if (unit->getID() == id) {
                unit->setXY(x,y);
                unit->setFacing(facing);
            }
        }
    }
}

//Deprecated.
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

//Deprecated.
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

//Currently not implemented. Processes server command to destroy unit.
void GameWindow::getUnitDeath(QString command)
{
    QStringList commandArgs = command.split(" ");

    int id = commandArgs.at(1).toInt();

    for (QObject *obj : this->gameDisplay->children()) {
        units *unit = dynamic_cast<units*>(obj);
        if (unit != NULL) {
            if (unit->getID() == id) {
                delete unit;
            }
        }
    }
}

//Currently not implemented. Processes server command regarding bullets.
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

//Initial processesing of all server commands.
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
            GameWindow::setWindowTitle("Player " + QString::number(team));
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
        case 100:
            doGameOver(commands.at(i));
            break;
        default:
            break;
        }
    }
}
