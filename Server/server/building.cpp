#include "building.h"


void Building::ontick()
{

}

void Building::updateState()
{

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
