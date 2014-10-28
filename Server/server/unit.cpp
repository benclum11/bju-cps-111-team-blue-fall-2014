#include "unit.h"

int Unit::nextID = 0;

void Unit::ontick()
{

}

Unit::Unit(bool isLiving)
{
    if (isLiving) {ID = nextID; ++nextID;}
    else {ID = -1;}
}

void Unit::updateState()
{

}
