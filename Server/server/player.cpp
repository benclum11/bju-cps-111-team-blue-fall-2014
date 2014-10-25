#include <QString>
#include "player.h"

Player::Player(int initHealth, int initMoney, int initTeam) {
    health = initHealth;
    money = initMoney;
    team = initTeam;
}

int Player::checkLevelofUnit(int type) {
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
        if(type.at(0) == '1') {
            for(int i = 1; i < type.length(); ++i) {
                specificType = specificType + type.at(i);
            }
        } else if (type.at(0) == '2') {
            for(int i = 1; i < type.length(); ++i) {
                specificType = specificType + type.at(i);
            }
        } else {}
        //needs to parse levels as well and im tired of this method
    }
}
