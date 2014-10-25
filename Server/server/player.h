#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "tile.h"

using namespace std;

class Player {

    int health, money, team;
    vector<int> unlockedBuildings, unlockedUnits;
    vector<Tile*> towerSpots;

public:
    Player(int, int, int);

    void setTowerSpots(vector<Tile*>& init) {towerSpots = init;}

    int checkLevelofUnit(int);

};

#endif // PLAYER_H
