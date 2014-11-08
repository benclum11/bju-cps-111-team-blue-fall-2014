#include "save.h"
#include "world.h"

using namespace std;


Save::Save(QString filename) {
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
                QString::number(unit->getYCoord()) + " " + QString::number(unit->getDirection());
        out << writeToFile << endl;
    }
}

