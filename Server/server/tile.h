#ifndef TILE_H
#define TILE_H

#include "building.h"
#include <string>

using namespace std;

class Tile {

    int xCoord, yCoord; // center of the tile
    bool buildable; //whether the tile can have a building
    Building* building; //building on the tile
    bool team; //If a building can be placed what team can place it

    void getCenterpoint(int& x, int& y) { x = xCoord; y = yCoord; }

public:
    Tile() {}

    void setBuildable(int init) { buildable = init; }
    void setXCoord(int init) { xCoord = init; }
    void setYCoord(int init) { yCoord = init; }
    void setTeam(bool init) { team = init; }
    void placeBuilding(Building* init) { building = init; }

    bool isBuildable() { return buildable; }

};

#endif // TILE_H
