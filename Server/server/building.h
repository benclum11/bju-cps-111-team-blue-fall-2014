#ifndef BUILDING_H
#define BUILDING_H

#include <vector>
#include "object.h"

using namespace std;

class Building : public Object {

    int type, attack, production, range, lvl, speed, totalcost;
    vector<int> unlock;

    void ontick();

public:
    Building() { totalcost = 0; }

    void setType(int init) { type = init; }
    void setAttack(int init) { attack = init; }
    void setProduction(int init) { production = init; }
    void setRange(int init) { range = init; }
    void setLevel(int init) { lvl = init; }
    void setSpeed(int init) { speed = init; }
    void setUnlock(vector<int>& init) { unlock = init; }
    void addtoTotalCost() { totalcost += cost; }

    int getType() {return type;}
    int getAttack() {return attack;}
    int getProduction() {return production;}
    int getRange() {return range;}
    int getLevel() {return lvl;}
    int getSpeed() {return speed;}
    vector<int> getUnlock() {return unlock;}
    int getTotalCost() {return totalcost;}

    void updateState();
    void upgrade(Building& upgrade);

};

#endif // BUILDING_H
