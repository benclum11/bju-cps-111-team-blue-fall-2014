#ifndef TILE_H
#define TILE_H

#include "building.h"
#include <string>

using namespace std;

class Tile {

    int xCoord, yCoord; // center of the tile
    bool buildable; //whether the tile can have a building
    Building* building; //building on the tile

    bool isBuildable() { return buildable; }

    void getCenterpoint(int& x, int& y) { x = xCoord; y = yCoord; }

public:
    Tile() {}

    void setBuildable(int init) { buildable = init; }
    void setXCoord(int init) { xCoord = init; }
    void setYCoord(int init) { yCoord = init; }
    void placeBuilding(Building* init) { building = init; }

};

#endif // TILE_H
