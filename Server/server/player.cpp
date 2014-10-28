#include "player.h"

Player::Player(int initHealth, int initMoney, int initTeam) : cheatMode(false)
{
    health = initHealth;
    money = initMoney;
    team = initTeam;
}

int Player::checkLevelofUnit(int type)
{
    return unlockedUnits[type];
}

void Player::setInitialUnlocks(vector<Building>& buildingData, vector<Unit>& unitData)
{
    for (uint i = 0; i < buildingData.size()/5; ++i) {
        unlockedBuildings.push_back(0);
    }
    for (uint i = 0; i < unitData.size()/5; ++i) {
        unlockedUnits.push_back(0);
    }
    unlockedBuildings[0] = 1;
    QStringList baseUnlocks = buildingData[0].getUnlock();
    for (int i = 0; i < baseUnlocks.size(); ++i) {
        QStringList unlock = baseUnlocks[i].split("_");
        int type = unlock.at(0).toInt();
        int specificType = unlock.at(1).toInt();
        int level = unlock.at(2).toInt();
        if(type == 1) {
            unlockedBuildings[specificType] = level;
        } else if (type == 2) {
            unlockedUnits[specificType] = level;
        }
    }
}

bool Player::attempttoSpendMoney(int amount)
{
    if (cheatMode) { return true; }
    if (amount < money || money < 0) {
        money -= amount;
        return true;
    }
    return false;
}

void Player::addToUnitCue(int specificType, int cost)
{
    if (cost < money || money < 0) {
        money -= cost;
        ++unitCues[specificType];
    }
}

bool Player::checkUnitCue(int specificType)
{
    if (unitCues[specificType] != 0) {
        --unitCues[specificType];
        return true;
    }
    return false;
}

int Player::getUnitCuesSize()
{
    return unitCues.size();
}
