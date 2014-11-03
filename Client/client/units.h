#include <QString>
#include <QLabel>
#ifndef UNITS_H
#define UNITS_H

class units
{
    int id, team, curHealth, maxHealth, x, y, facing;
    QString type;
    QLabel* image;

public:
    units(QString unitType, int loyalty, int health, int xCoord, int yCoord, int direction);

    void setXY (int xCoord, int yCoord);
    void setFacing(int direction);
    void setCurHealth(int health);
    void killUnit();
};

#endif // UNITS_H
