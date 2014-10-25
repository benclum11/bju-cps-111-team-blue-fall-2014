//open highscore file
//compare if finalScore is higher than highScore
//set new highscore and name
//allow viewing of current highscore and highscore-ee

#include "highscore.h"

HighScore::HighScore()
{
    //Load highscore from savd file.
    //If no previous file, set score to 0
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
    //Should we check here that new score is higher? Or just in checkHScore?
    currentHScore = newScore;
    highSName = newName;
}

//Unit Tests (Where do I put these?)
assert(HighScore::checkHScore(100));
HighScore::newHScore("User");
assert(HighScore::getHScore() == 100);
assert(HighScore::getHSName() == "User");

assert(!HighScore::checkHScore(50));
