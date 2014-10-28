#include <QString>
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
    vector<int> baseUnlocks = buildingData[0].getUnlock();
    for (unsigned int i = 0; i < baseUnlocks.size(); ++i) {
        QString type = QString::number(baseUnlocks[i]);
        QString specificType = "";
        int level = ((QString)(type.at(type.length() - 1))).toInt();
        if(type.at(0) == '1') {
            for(int i = 1; i < type.length() - 1; ++i) {
                specificType = specificType + type.at(i);
                unlockedBuildings[specificType.toInt()] = level;
            }
        } else if (type.at(0) == '2') {
            for(int i = 1; i < type.length() - 1; ++i) {
                specificType = specificType + type.at(i);
                unlockedUnits[specificType.toInt()] = level;
            }
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

void Player::addToUnitCue(int type, int cost)
{
    if (cost < money || money < 0) {
        money -= cost;
        ++unitCues[type];
    }
}

bool Player::checkUnitCue(int type)
{
    if (unitCues[type] != 0) {
        --unitCues[type];
        return true;
    }
    return false;
}

int Player::getUnitCuesSize()
{
    return unitCues.size();
}
