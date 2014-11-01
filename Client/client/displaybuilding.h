#ifndef DISPLAYBUILDING_H
#define DISPLAYBUILDING_H

#include <QString>
#include <QStringList>
#include <QPixmap>
#include "stats.h"
#include "buildablelabel.h"

class DisplayBuilding : public BuildableLabel {

    QString type;
    int attack, nextLvlAttack, speed, nextLvlSpeed, range, nextLvlRange, production,
    nextLvlProduction, cost, nextLvlCost;

    QStringList nextLvlUnlocks;

public:

    DisplayBuilding(QWidget *parent, Stats currentStats, int nextLvlAttack, int nextLvlSpeed,
                    int nextLvlRange, int nextLvlProduction, int nextLvlCost, QStringList nextLvlUnlocks);

};

#endif // DISPLAYBUILDING_H
