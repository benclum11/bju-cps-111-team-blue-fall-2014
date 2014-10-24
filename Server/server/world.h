#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <QTextStream>
#include "building.h"
#include "unit.h"
#include "tile.h"
#include "player.h"

using namespace std;

class World {

    static World* world;
    vector<Unit> unitTypes;
    vector<Building> buildingTypes;
    Tile*** map;
    vector<Object*> object;
    vector<Tile*> team1path;
    vector<Tile*> team2path;
    vector<Player*> players;

    World();

    void readMapFile();
    void readTileInfo(QTextStream&, Tile*);
    void readPaths(QTextStream&);
    void readTowerFile();
    void readTowerInfo(QTextStream&);
    void readBaseLocation(QTextStream&);

public:

    static World* Instance();
    Building getBuildingType(int);

};


#endif // WORLD_H
