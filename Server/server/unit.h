#ifndef UNIT_H
#define UNIT_H

#include "object.h"

class Unit : public Object {

    int ID, health, speed, damage, direction;
    bool endOfPath;
    int indexOfPath;

public:
    Unit();

    void setHealth(int init) {health = init;}
    void setSpeed(int init) {speed = init;}
    void setDamage(int init) {damage = init;}
    void setDirection(int init) {direction = init;}
    void incrementIndexOfPath() {++indexOfPath;}
    void setId(int init) {ID = init;}
    void setEndOfPath(bool init) {endOfPath = init;}
    void setIndexOfPath(int init) {indexOfPath = init;}

    int getHealth() {return health;}
    int getSpeed() {return speed;}
    int getDamage() {return damage;}
    int getDirection() {return direction;}
    int getIndexOfPath() {return indexOfPath;}
    int getID() {return ID;}
    bool getEndOfPath() {return endOfPath;}
};

#endif // UNIT_H
