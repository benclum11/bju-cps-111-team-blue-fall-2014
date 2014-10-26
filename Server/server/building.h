#ifndef BUILDING_H
#define BUILDING_H

#include <vector>
#include "object.h"

using namespace std;

class Building : public Object {

    int type, attack, production, range, lvl, speed;
    vector<int> unlock;

    void ontick();

public:
    Building() {}

    void setType(int init) { type = init; }
    void setAttack(int init) { attack = init; }
    void setProduction(int init) { production = init; }
    void setRange(int init) { range = init; }
    void setLevel(int init) { lvl = init; }
    void setSpeed(int init) { speed = init; }
    void setUnlock(vector<int>& init) { unlock = init; }

    int getType() {return type;}
    int getAttack() {return attack;}
    int getProduction() {return production;}
    int getRange() {return range;}
    int getLevel() {return lvl;}
    int getSpeed() {return speed;}
    vector<int> getUnlock() {return unlock;}

    void updateState();
    void upgrade(Building& upgrade);

};

#endif // BUILDING_H
