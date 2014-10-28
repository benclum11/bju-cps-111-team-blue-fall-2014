#ifndef OBJECT_H
#define OBJECT_H

class Object {

    virtual void ontick() = 0;

protected:
    int xCoord, yCoord, team, cost;

public:

    virtual void updateState() = 0;

    void setTeam(int init) { team = init; }
    void setCost(int init) { cost = init; }
    void setXCoord(int init) { xCoord = init; }
    void setYCoord(int init) { yCoord = init; }

    int getCost() { return cost; }
};

#endif // OBJECT_H
