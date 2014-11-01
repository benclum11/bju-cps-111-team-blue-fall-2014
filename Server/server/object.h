#ifndef OBJECT_H
#define OBJECT_H

#include <QString>

class Object {

protected:
    int xCoord, yCoord, team, cost;
    QString type;

public:

    void setType(QString init) { type = init; }
    void setTeam(int init) { team = init; }
    void setCost(int init) { cost = init; }
    void setXCoord(int init) { xCoord = init; }
    void setYCoord(int init) { yCoord = init; }

    QString getType() {return type;}
    int getTeam() {return team;}
    int getCost() { return cost; }
    int getXCoord() {return xCoord;}
    int getYCoord() {return yCoord;}
};

#endif // OBJECT_H
