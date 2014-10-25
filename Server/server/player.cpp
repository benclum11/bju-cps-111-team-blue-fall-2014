#include "player.h"
#include "world.h"

Player::Player(int initHealth, int initMoney, int initTeam) {
    health = initHealth;
    money = initMoney;
    team = initTeam;
    unlockedUnits = {0,0,0,0,0,0,0,0,0,0};
    unlockedBuildings = {0,0,0,0,0,0,0,0,0,0};
}

int Player::checkLevelofUnit(int type) {
    return unlockedUnits[type];
}
