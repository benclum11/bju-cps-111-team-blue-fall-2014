#ifndef OBJECT_H
#define OBJECT_H

class Object {

    virtual void ontick() = 0;

protected:
    int ID, xCoord, yCoord, team;

public:

};

#endif // OBJECT_H
