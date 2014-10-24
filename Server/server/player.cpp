#include "player.h"
#include "world.h"

Player::Player(int initHealth, int initMoney, int initTeam) {
    health = initHealth;
    money = initMoney;
    team = initTeam;
    World::Instance()->getBuildingType(111);
}
