#include "building.h"

bool Building::checkCounter()
{
    if (counter == 0) {
        counter = 50;
        return true;
    } else {
        --counter;
        return false;
    }
}

void Building::upgrade(Building &upgrade)
{
    type = upgrade.getType();
    attack = upgrade.getAttack();
    production = upgrade.getProduction();
    range = upgrade.getRange();
    speed = upgrade.getSpeed();
    unlock = upgrade.getUnlock();
    cost = upgrade.getCost();
}
