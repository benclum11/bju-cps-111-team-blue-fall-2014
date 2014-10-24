#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <QTextStream>
#include "building.h"
#include "unit.h"
#include "tile.h"

using namespace std;

class World {

    static World* world;
    vector<Unit> unitTypes;
    vector<Building> buildingTypes;
    Tile*** map;
    vector<Object*> object;
    vector<Tile*> team1path;
    vector<Tile*> team2path;
    vector<Tile*> team1towers;
    vector<Tile*> team2towers;

    World();

    void readMapFile();
    void readTileInfo(QTextStream&, Tile*);
    void readPaths(QTextStream&);
    void readTowerSpots(QTextStream&);
    void readTowerFile();
    void readTowerInfo(QTextStream&);
    void readBaseLocation(QTextStream&);

public:

    static World* Instance();

};


#endif // WORLD_H
