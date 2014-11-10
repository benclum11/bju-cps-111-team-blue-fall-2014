#include "load.h"
#include <QDir>
#include <QDebug>

using namespace std;
Load::Load(QString filename) {
    filename.replace(QString("\n"), QString(""));
    QFile file(QString("../server/saved/") + filename + ".txt");
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
            QStringList typeList;
            for (int i = 0; i < data.size(); ++i) {
                if (data.at(i).contains("_")) { typeList = data.at(i).split("_"); }
            }

            if (typeList.at(0).toInt() == 1) { //create building
                Tile* tile = World::Instance()->findTileAt(data.at(0).toInt(), data.at(1).toInt());
                int cost = World::Instance()->getBuildingType(data.at(2)).getCost();
                if (World::Instance()->getPlayer(tile->getTeam())->attempttoSpendMoney(cost)) {
                    World::Instance()->buildTower(data.at(2), tile);
                    tile->getBuilding()->addtoTotalCost();
                }
            } else if (typeList.at(0).toInt() == 2) { //create unit
                int team = 1;
                if (data.at(2).toInt() < 250) { team = 1; }
                if (data.at(2).toInt() > 250) { team = 2; }
                World::Instance()->loadUnit(data.at(1), team, data.at(2).toInt(), data.at(3).toInt(), data.at(4).toInt());

            }
        }
    }
}
