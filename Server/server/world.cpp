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

<<<<<<< HEAD
    QFile mapFile("://textfiles/map.txt");
    if (!mapFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return;
    }
    QTextStream readMap(&mapFile);
    QString temp = readMap.readLine();
    int rows = temp.toInt();
    temp = readMap.readLine();
    int columns = temp.toInt();
=======
    ifstream readmap("://textfiles/map.txt");
    string temp;
    getline(readmap, temp);
    int rows = stoi(temp);
    getline(readmap,temp);
    int columns = stoi(temp);
>>>>>>> parent of 1df6558... Infile cant open file

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

void World::readTowerFile() {

}
