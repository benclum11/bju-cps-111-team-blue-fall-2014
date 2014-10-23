#ifndef WORLD_H
#define WORLD_H

#include <vector>
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

    World();

    void readMapFile();

public:

    static World* Instance();

};

#endif // WORLD_H
