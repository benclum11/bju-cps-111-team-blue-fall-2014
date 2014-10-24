#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <fstream>
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

    World();

    void readMapFile();
    void readTileInfo(ifstream&, Tile*);
    void readPaths(ifstream&);

public:

    static World* Instance();

};


#endif // WORLD_H
