#ifndef UNIT_H
#define UNIT_H

#include "object.h"

class Unit : Object {

    int health, speed, damage, size;

    void ontick();

public:
    Unit() {}

    void updateState();

};

#endif // UNIT_H
