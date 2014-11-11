#include <QString>
#include <QLabel>
#ifndef UNITS_H
#define UNITS_H

class units : public QLabel
{
    int id, x, y, facing, type;
    //QLabel* image; //This is depricated now

public:
    units(int ID, QString unitType, int xCoord, int yCoord, int direction, QWidget *display);

    int getID() {return id;}

    void setXY (int xCoord, int yCoord);
    void setFacing(int direction);
    void setCurHealth(int health);
    void killUnit();
    bool processType(QString unitType, units *instance);
};

#endif // UNITS_H
