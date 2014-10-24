#include "world.h"
#include <string>
#include <iostream>
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

}

void World::readMapFile() {

    ifstream readmap;
    readmap.open("://textfiles/map.txt");
    char temp[10];
    readmap.getline(temp,3);
    int rows = stoi(temp);
    readmap.getline(temp,3);
    int columns = stoi(temp);

    map = new Tile**[rows];
    for (int i = 0; i < rows; ++i) {
        map[i] = new Tile*[columns];
        for (int j = 0; j < columns; ++j) {
            map[i][j] = new Tile();
            readTileInfo(readmap, map[i][j]);
        }
    }
    readPaths(readmap);
    readmap.close();
}

void World::readTileInfo(ifstream& readmap, Tile* tile) {
    char temp[50];
    readmap.getline(temp, 40);
    QString line = temp;
    QStringList data = line.split(" ");
    tile->setBuildable(data[0] == "1");
    tile->setXCoord(data[1].toInt());
    tile->setYCoord(data[2].toInt());
}

void World::readPaths(ifstream& readmap) {
    char temp[50];
    readmap.getline(temp, 40);
    QString line = temp;
    QStringList data = line.split(" ");
    for (int i = 0; i < data.length(); ++i) {
        QStringList point = data[i].split(",");
        Tile* tile = map[point[1].toInt()][point[0].toInt()];
        team1path.push_back(tile);
    }
    readmap.getline(temp, 40);
    line = temp;
    data = line.split(" ");
    for (int i = 0; i < data.length(); ++i) {
        QStringList point = data[i].split(",");
        Tile* tile = map[point[1].toInt()][point[0].toInt()];
        team2path.push_back(tile);
    }
}
