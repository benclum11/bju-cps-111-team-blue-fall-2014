#ifndef PLAYER_H
#define PLAYER_H

#include <vector>

using namespace std;

class Player {

    int health, money, team;
    vector<int> unlocked;

public:
    Player(int, int, int);

};

#endif // PLAYER_H
