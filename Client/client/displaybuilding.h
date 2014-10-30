#ifndef DISPLAYBUILDING_H
#define DISPLAYBUILDING_H

#include <QLabel>
#include <QString>
#include <QStringList>
#include <QPixmap>
#include "stats.h"

class DisplayBuilding : public QLabel {

    QString type;
    int attack, nextLvlAttack, speed, nextLvlSpeed, range, nextLvlRange, production,
    nextLvlProduction, cost, nextLvlCost;

    QStringList nextLvlUnlocks;

public:

    DisplayBuilding(QWidget *parent, Stats currentStats, int nextLvlAttack, int nextLvlSpeed,
                    int nextLvlRange, int nextLvlProduction, int nextLvlCost, QStringList nextLvlUnlocks);

};

#endif // DISPLAYBUILDING_H
