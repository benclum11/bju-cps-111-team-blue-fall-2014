#include <QString>
#include <QLabel>
#ifndef UNITS_H
#define UNITS_H

class units
{
    int id, team, curHealth, maxHealth, x, y, facing, type, level;
    QLabel* image;

public:
    units(QString unitType, int loyalty, int health, int xCoord, int yCoord, int direction, QWidget *display);

    void setXY (int xCoord, int yCoord);
    void setFacing(int direction);
    void setCurHealth(int health);
    void killUnit();
    bool processType(QString unitType, units *instance);
};

#endif // UNITS_H
