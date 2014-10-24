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

World::World() {

    readMapFile();
    readTowerFile();

}

void World::readMapFile() {

    QFile mapFile("://textfiles/map.txt");
    if (!mapFile.open(QIODevice::ReadOnly | QIODevice::Text)) { return; }
    QTextStream readMap(&mapFile);
    QString temp = readMap.readLine();
    int rows = temp.toInt();
    temp = readMap.readLine();
    int columns = temp.toInt();

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
    readTowerSpots(readMap);
    mapFile.close();
}

void World::readTileInfo(QTextStream& readMap, Tile* tile) {
    QString temp = readMap.readLine();
    QStringList data = temp.split(" ");
    tile->setBuildable(data[0] == "1");
    tile->setXCoord(data[1].toInt());
    tile->setYCoord(data[2].toInt());
}

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

void World::readTowerSpots(QTextStream& readMap) {
    QString temp = readMap.readLine();
    QStringList data = temp.split(" ");
    for (int i = 0; i < data.length(); ++i) {
        QStringList point = data[i].split(",");
        Tile* tile = map[point[1].toInt()][point[0].toInt()];
        team1towers.push_back(tile);
    }
    temp = readMap.readLine();
    data = temp.split(" ");
    for (int i = 0; i < data.length(); ++i) {
        QStringList point = data[i].split(",");
        Tile* tile = map[point[1].toInt()][point[0].toInt()];
        team2towers.push_back(tile);
    }
}

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

void World::readTowerInfo(QTextStream& readBuildings)
{
    QString temp = readBuildings.readLine();
    QStringList data = temp.split(" ");
    Building tempbuilding;

    tempbuilding.setType(data[0].toInt());
    tempbuilding.setLevel(data[1].toInt());
    tempbuilding.setHealth(data[2].toInt());
    tempbuilding.setAttack(data[3].toInt());
    tempbuilding.setProduction(data[4].toInt());
    tempbuilding.setRange(data[5].toInt());
    tempbuilding.setSpeed(data[6].toInt());

    if (data[7] != "0") {
        QStringList tempunlocks = data[7].split(",");
        vector<int> unlocks;
        for(int i = 0; i < tempunlocks.length(); ++i) {
            unlocks.push_back(tempunlocks[i].toInt());
        }
        tempbuilding.setUnlock(unlocks);
    }
    buildingTypes.push_back(tempbuilding);
}

void World::readBaseLocation(QTextStream &)
{

}
