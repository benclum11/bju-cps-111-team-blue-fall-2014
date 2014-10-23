#ifndef BASE_H
#define BASE_H

#include "building.h"

    class Base : Building {

        int health, money;

        void ontick();

    };

#endif // BASE_H
