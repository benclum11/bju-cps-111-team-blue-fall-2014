#include "save.h"
#include "world.h"

using namespace std;


Save::Save(QString filename) {
    filename.replace(QString("\n"), QString(""));
    QFile file;
    file.setFileName(filename + ".txt");
    file.open(QIODevice::ReadWrite | QIODevice::Text);
    saveFile(file);
    file.close();
}

//read info of every building, unit, any additional info and write to file
void Save::saveFile(QFile &file) {
    QTextStream out(&file);

    //needs more for counters. How do I get "all" the counters?
    out << World::Instance()->getCounter() << endl;

    //player 1 info
    QString player1 = QString("player 1 ") + QString::number(World::Instance()->getPlayer(1)->getMoney()) +
            " " + QString::number(World::Instance()->getPlayer(1)->getHealth());
    out << player1 << endl;

    //player 2 info
    QString player2 = QString("player 2 ") + QString::number(World::Instance()->getPlayer(2)->getMoney()) +
            " " + QString::number(World::Instance()->getPlayer(2)->getHealth());
    out << player2 << endl;

    for (int y = 0; y < World::Instance()->getRows(); ++y) {
        for (int x = 0; x < World::Instance()->getColumns(); ++x) {
            Tile* tile = World::Instance()->getTile(y,x);
            if (tile->isBuildable()) {
                Building* building = tile->getBuilding();
                if (building != nullptr){
                    QString writeToFile = QString::number(tile->getXCoord()) + " " + QString::number(tile->getYCoord()) + " " + building->getType() + " " +
                            QString::number(tile->getTeam()) + " " + QString::number(building->getAttack()) + " " + QString::number(building->getSpeed()) + " " +
                            QString::number(building->getRange()) + " " + QString::number(building->getProduction()) + " " + QString::number(building->getCost());
                    out << writeToFile << endl;
                }
            }
        }
    }
    vector<Unit*> livingUnits = World::Instance()->getLivingUnits();
    for (unsigned int x = 0; x < livingUnits.size(); ++x) {
        Unit* unit = livingUnits.at(x);
        QString writeToFile = QString::number(unit->getID()) + " " + unit->getType() + " " + QString::number(unit->getXCoord()) + " " +
                QString::number(unit->getYCoord()) + " " + QString::number(unit->getDirection()) + " " + QString::number(unit->getIndexOfPath());
        out << writeToFile << endl;
    }
}

