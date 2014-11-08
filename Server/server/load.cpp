#include "load.h"

using namespace std;
Load::Load(QString filename) {
    QFile file(filename + ".txt");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    loadFile(file);
    file.close();
}


//Build every tower, base, unit, from new file
void Load::loadFile(QFile &file) {
    QTextStream in(&file);


    while(!in.atEnd()) {
        QString line = in.readLine();
        QStringList data = line.split(" ");

        if (data.size() == 1) {
            World::Instance()->setCounter(data.at(0).toInt());
        } else {
            QStringList typeList = data.at(2).split("_");

            if (typeList.at(0).toInt() == 1) { //create building
                Tile* tile = World::Instance()->findTileAt(data.at(0).toInt(), data.at(1).toInt());
                int cost = World::Instance()->getBuildingType(data.at(2)).getCost();
                if (World::Instance()->getPlayer(tile->getTeam())->attempttoSpendMoney(cost)) {
                    World::Instance()->buildTower(data.at(2), tile);
                    tile->getBuilding()->addtoTotalCost();
                }
            } else if (typeList.at(0).toInt() == 2) { //create unit

            }
        }
    }
}


