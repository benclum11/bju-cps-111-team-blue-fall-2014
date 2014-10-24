//open highscore file
//compare if finalScore is higher than highScore
//set new highscore and name
//allow viewing of current highscore and highscore-ee

#include "highscore.h"

HighScore::HighScore()
{

}

//Returns true if given score is higher than current high-score. Stores score in newHScore.
bool HighScore::checkHScore(int finalScore)
{
    if (finalScore > currentHScore)
    {
        newScore = finalScore;
        return true;
    } else
    {
        return false;
    }
}

//Sets <score> as new high-score and <highSName> as new highscore-ee
void HighScore::newHScore(std::string newName)
{
    currentHScore = newScore;
    highSName = newName;
}
