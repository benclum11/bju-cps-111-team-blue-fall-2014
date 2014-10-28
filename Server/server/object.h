#ifndef OBJECT_H
#define OBJECT_H

#include <QString>

class Object {

    virtual void ontick() = 0;

protected:
    int xCoord, yCoord, team, cost;
    QString type;

public:

    virtual void updateState() = 0;

    void setType(QString init) { type = init; }
    void setTeam(int init) { team = init; }
    void setCost(int init) { cost = init; }
    void setXCoord(int init) { xCoord = init; }
    void setYCoord(int init) { yCoord = init; }

    QString getType() {return type;}
    int getCost() { return cost; }
};

#endif // OBJECT_H
