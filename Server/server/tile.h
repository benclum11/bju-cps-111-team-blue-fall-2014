#ifndef TILE_H
#define TILE_H

#include "building.h"
#include <string>

using namespace std;

class Tile {

    int xCoord, yCoord; // center of the tile
    bool buildable; //whether the tile can have a building
    Building* building; //building on the tile
    int team; //0 for neutral 1 or 2 for buildables

    void getCenterpoint(int& x, int& y) { x = xCoord; y = yCoord; }

public:
    Tile() { building = nullptr; }

    void setBuildable(int init) { buildable = init; }
    void setXCoord(int init) { xCoord = init; }
    void setYCoord(int init) { yCoord = init; }
    void setTeam(bool init) { team = init; }
    void placeBuilding(Building* init) { building = init; }

    bool isBuildable() { return buildable; }
    Building* getBuilding() { return building; }

};

#endif // TILE_H
