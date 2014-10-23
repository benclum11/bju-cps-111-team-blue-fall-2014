#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include "object.h"
#include "building.h"
#include "unit.h"
#include "tile.h"

using namespace std;

class World {

    World* world;
    vector<Unit> unitTypes;
    vector<Building> buildingTypes;
    Tile*** map;
    vector<Object*> livingTypes;

public:

    World* Instance();

};

#endif // WORLD_H
