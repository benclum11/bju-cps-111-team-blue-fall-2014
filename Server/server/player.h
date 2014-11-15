#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "tile.h"
#include "building.h"
#include "unit.h"

using namespace std;

class Player {

    int health, money, team;
    vector<int> unlockedBuildings, unlockedUnits, unitCues;
    vector<Tile*> towerSpots;
    bool cheatMode;

public:
    Player(int, int, int);

    void setTowerSpots(vector<Tile*>& init) {towerSpots = init;}

    int checkLevelofUnit(int);

    void setInitialUnlocks(vector<Building>&, vector<Unit>&);

    bool attemptToSpendMoney(int);

    void addToUnitCue(int, int);

    bool checkUnitCue(int);

    int getUnitCuesSize();

    int getTeam() {return team;}
    int getHealth() {return health;}
    int getMoney() {return money;}

    void setMoney(int init) { money = init; }
    void setHealth(int init) { health = init; }
    void setCheatMode(bool init) { cheatMode = init; }


    vector<int> getUnlockedBuildings() {return unlockedBuildings;}
    vector<int> getUnlockedUnits() {return unlockedUnits;}

};

#endif // PLAYER_H
