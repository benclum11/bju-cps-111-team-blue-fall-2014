#ifndef OBJECT_H
#define OBJECT_H

class Object {

    virtual void ontick() = 0;

protected:
    int ID, xCoord, yCoord, team;

public:

    virtual void updateState() = 0;

};

#endif // OBJECT_H
