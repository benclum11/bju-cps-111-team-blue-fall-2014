#ifndef HIGHSCORE_H
#define HIGHSCORE_H
#include <string>

class HighScore {

    int newScore;
    int currentHScore;
    std::string highSName;

public:
    HighScore();
    bool checkHScore(int finaleScore); //Should we include this? Why not check and set in the same method?
    void newHScore(std::string newName);
    //Needs file load/save logic.

    //getters
    int getHScore() { return currentHScore; }
    std::string getHSName() { return highSName; }

};

#endif // HIGHSCORE_H
