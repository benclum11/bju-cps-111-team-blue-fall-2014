#ifndef UNIT_H
#define UNIT_H

#include "object.h"

class Unit : public Object {

    static int nextID;

    int ID, health, speed, damage, size;

    void ontick();

public:
    Unit(bool);

    void updateState();

    void setHealth(int init) {health = init;}
    void setSpeed(int init) {speed = init;}
    void setDamage(int init) {damage = init;}

    int getHealth() {return health;}
    int getSpeed() {return speed;}
    int getDamage() {return damage;}

};

#endif // UNIT_H
