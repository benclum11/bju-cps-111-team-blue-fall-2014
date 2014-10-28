#ifndef UNIT_H
#define UNIT_H

#include "object.h"

class Unit : public Object {

    static int nextID;

    int ID, health, speed, damage, size;

    void ontick();

public:
    Unit() {ID = nextID; ++nextID;}

    void updateState();

};

#endif // UNIT_H
