#include "tile.h"


int Tile::destroyBuilding()
{
    int cost = building->getTotalCost();
    delete building;
    return cost/2;
}
