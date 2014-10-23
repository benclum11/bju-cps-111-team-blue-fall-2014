#ifndef BUILDING_H
#define BUILDING_H

#include "object.h"

class Building : Object {

    int type, attack, production, range, lvl, speed, unlock;

    virtual void ontick();

};

#endif // BUILDING_H
