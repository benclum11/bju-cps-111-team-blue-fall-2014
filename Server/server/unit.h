#ifndef UNIT_H
#define UNIT_H

#include "object.h"

class Unit : public Object {

    static int nextID;

    int ID, health, speed, damage, direction;
    bool endOfPath;
    int indexOfPath;

public:
    Unit(bool);

    void setHealth(int init) {health = init;}
    void setSpeed(int init) {speed = init;}
    void setDamage(int init) {damage = init;}
    void setDirection(int init) {direction = init;}
    void incrementIndexOfPath() {++indexOfPath;}
    void setEndOfPath(bool init) {endOfPath = init;}

    int getHealth() {return health;}
    int getSpeed() {return speed;}
    int getDamage() {return damage;}
    int getDirection() {return direction;}
    int getIndexOfPath() {return indexOfPath;}
    int getID() {return ID;}
    bool getEndOfPath() {return endOfPath;}
};

#endif // UNIT_H
