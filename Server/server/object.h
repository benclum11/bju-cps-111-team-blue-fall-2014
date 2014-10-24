#ifndef OBJECT_H
#define OBJECT_H

class Object {

    int ID, xCoord, yCoord;

    virtual void ontick() = 0;

};

#endif // OBJECT_H
