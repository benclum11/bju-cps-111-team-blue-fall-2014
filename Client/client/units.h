#include <QString>
#include <QLabel>
#include <QProgressBar>
#ifndef UNITS_H
#define UNITS_H

class units : public QLabel
{
    int id, x, y, facing, type;

public:
    units(int ID, QString unitType, int xCoord, int yCoord, int direction, QWidget *display);

    int getID() {return id;}
    QProgressBar* healthbar;

    void setXY (int xCoord, int yCoord);
    void setFacing(int direction);
    void setCurHealth(int health);
    void killUnit();
    bool processType(QString unitType, units *instance);
};

#endif // UNITS_H
