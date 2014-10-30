#include "displaybuilding.h"
#include <QFile>


DisplayBuilding::DisplayBuilding(QWidget *parent, Stats currentStats, int nextLvlAttack1, int nextLvlSpeed1, int nextLvlRange1,
                                 int nextLvlProduction1, int nextLvlCost1, QStringList nextLvlUnlocks1) : QLabel(parent)
{
    QStringList type = currentStats.getType().split("_");

    setPixmap(QPixmap("://Resources/Buildings/" + type.at(1) + ".png"));

    attack = currentStats.getAttack();
    speed = currentStats.getSpeed();
    range = currentStats.getRange();
    production = currentStats.getProduction();
    cost = currentStats.getCost();

    nextLvlAttack = nextLvlAttack1;
    nextLvlSpeed = nextLvlSpeed1;
    nextLvlCost = nextLvlCost1;
    nextLvlRange = nextLvlRange1;
    nextLvlProduction = nextLvlProduction1;
    nextLvlUnlocks = nextLvlUnlocks1;

}
