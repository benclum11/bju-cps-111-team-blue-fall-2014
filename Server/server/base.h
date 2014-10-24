#ifndef BASE_H
#define BASE_H

#include "building.h"

class Base : Building {

    int health, money;

    void ontick();

public:
    void setHealth(int init) { health = init; }

};

#endif // BASE_H
