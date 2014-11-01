#include "unit.h"

int Unit::nextID = 0;

Unit::Unit(bool isLiving) : direction(0), indexOfPath(1)
{
    if (isLiving) {ID = nextID; ++nextID;}
    else {ID = -1;}
    if (nextID == 1000) {nextID = 0;}
}
