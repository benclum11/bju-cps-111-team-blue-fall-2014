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
    units();
};

#endif // UNITS_H
