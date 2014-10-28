#ifndef BUILDING_H
#define BUILDING_H

#include <vector>
#include <QString>
#include <QStringList>
#include "object.h"

using namespace std;

class Building : public Object {

    int attack, production, range, speed, totalcost;
    QStringList unlock;

    void ontick();

public:
    Building() { totalcost = 0; }

    void setAttack(int init) { attack = init; }
    void setProduction(int init) { production = init; }
    void setRange(int init) { range = init; }
    void setSpeed(int init) { speed = init; }
    void setUnlock(QStringList& init) { unlock = init; }
    void addtoTotalCost() { totalcost += cost; }

    int getAttack() {return attack;}
    int getProduction() {return production;}
    int getRange() {return range;}
    int getSpeed() {return speed;}
    QStringList& getUnlock() {return unlock;}
    int getTotalCost() {return totalcost;}

    void updateState();
    void upgrade(Building& upgrade);

};

#endif // BUILDING_H
