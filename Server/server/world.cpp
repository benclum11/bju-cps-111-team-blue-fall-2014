#include "world.h"
#include <string>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QStringList>

using namespace std;

// Global static pointer used to ensure a single instance of the class.
World* World::world = NULL;

World* World::Instance() {
    if(!world) {
        world = new World();
    }
    return world;
}

//returns a copy of the building type
Building World::getBuildingType(int type)
{
    for(unsigned int i = 0; i < buildingTypes.size(); ++i) {
        if(buildingTypes[i].getType() == type) {
            return buildingTypes[i];
        }
    }
    Building fail;
    return fail;
}

//returns a copy of the unit type
Unit World::getUnitType(int type)
{

}

//places a tower of specified type in the specified tile
void World::buildTower(int type, Tile* tile)
{

}

//deploys a unit of specified type on specified team
void World::deployUnit(int type, int team)
{

}

//runs every 20 milliseconds
void World::updateWorld()
{
    for(unsigned int i = 0; i < livingUnits.size(); ++i)
    {
        livingUnits[i]->updateState();
    }
    for(int i = 0; i < rows; ++i) {
        for(int j = 0; j < columns; ++j) {
            if (map[i][j]->isBuildable() && map[i][j]->getBuilding() != nullptr) {
                map[i][j]->getBuilding()->updateState();
            }
        }
    }
}

//checks to see whether this interval is the one to deploy
void World::canDeployUnits()
{
    if (counter == 0)
    {
        for(unsigned int i = 0; i < team1unitCues.size(); ++i) {
            deployUnit(i, 1);
            --team1unitCues[i];
        }

        for(unsigned int i = 0; i < team2unitCues.size(); ++i) {
            deployUnit(i, 2);
            --team2unitCues[i];
        }
        counter = 150;
    } else { --counter; }
}

//constructs the initial game state
World::World() : counter(500) {

    readMapFile();
    readTowerFile();
    readUnitFile();

}

//reads the initial map state
void World::readMapFile() {

    QFile mapFile("://textfiles/map.txt");
    if (!mapFile.open(QIODevice::ReadOnly | QIODevice::Text)) { return; }
    QTextStream readMap(&mapFile);
    QString temp = readMap.readLine();
    rows = temp.toInt();
    temp = readMap.readLine();
    columns = temp.toInt();

    map = new Tile**[rows];
    for (int i = 0; i < rows; ++i) {
        map[i] = new Tile*[columns];
        for (int j = 0; j < columns; ++j) {
            Tile* tempTile = new Tile();
            readTileInfo(readMap, tempTile);
            map[i][j] = tempTile;
        }
    }
    readPaths(readMap);
    mapFile.close();
}

//reads individual tile info
void World::readTileInfo(QTextStream& readMap, Tile* tile) {
    QString temp = readMap.readLine();
    QStringList data = temp.split(" ");
    tile->setBuildable(data[0] == "1");
    tile->setXCoord(data[1].toInt());
    tile->setYCoord(data[2].toInt());
    tile->setTeam(data[3].toInt());
}

//reads what paths the units will use
void World::readPaths(QTextStream& readMap) {
    QString temp = readMap.readLine();
    QStringList data = temp.split(" ");
    for (int i = 0; i < data.length(); ++i) {
        QStringList point = data[i].split(",");
        Tile* tile = map[point[1].toInt()][point[0].toInt()];
        team1path.push_back(tile);
    }
    temp = readMap.readLine();
    data = temp.split(" ");
    for (int i = 0; i < data.length(); ++i) {
        QStringList point = data[i].split(",");
        Tile* tile = map[point[1].toInt()][point[0].toInt()];
        team2path.push_back(tile);
    }
}

//reads the stats of the types of towers
void World::readTowerFile() {
    QFile buildingFile("://textfiles/buildings.txt");
    if (!buildingFile.open(QIODevice::ReadOnly | QIODevice::Text)) { return; }
    QTextStream readBuildings(&buildingFile);
    QString temp = readBuildings.readLine();
    for (int i = 0; i < temp.toInt(); ++i) {
        for (int i = 0; i < 5; ++i) {
            readTowerInfo(readBuildings);
        }
    }
    readBaseLocation(readBuildings);
}

//reads individual tower stats
void World::readTowerInfo(QTextStream& readBuildings)
{
    QString temp = readBuildings.readLine();
    QStringList data = temp.split(" ");
    Building tempbuilding;

    tempbuilding.setType(data[0].toInt());
    tempbuilding.setLevel(data[1].toInt());
    tempbuilding.setAttack(data[2].toInt());
    tempbuilding.setProduction(data[3].toInt());
    tempbuilding.setRange(data[4].toInt());
    tempbuilding.setSpeed(data[5].toInt());

    if (data[6] != "0") {
        QStringList tempunlocks = data[6].split(",");
        vector<int> unlocks;
        for(int i = 0; i < tempunlocks.length(); ++i) {
            unlocks.push_back(tempunlocks[i].toInt());
        }
        tempbuilding.setUnlock(unlocks);
    }
    buildingTypes.push_back(tempbuilding);
}

//reads the starting location for base and creates one there
void World::readBaseLocation(QTextStream& readBuildings)
{
    QString temp = readBuildings.readLine();
    QStringList data = temp.split(" ");
    QStringList basePoint = data[0].split(",");
    Building* base = new Building(buildingTypes[0]);

    map[basePoint[1].toInt()][basePoint[0].toInt()]->placeBuilding(base);
}

//reads the stats of the types of units
void World::readUnitFile()
{

}
