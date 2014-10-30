#ifndef STATS_H
#define STATS_H

#include <QString>
#include <QStringList>

class Stats {
    QString type;
    int attack, speed, range ,production, health, cost;
    QStringList unlock;

public:
    Stats(QString type,int attack,int speed,int range,int production,int cost,QStringList unlock):
        type(type), attack(attack), speed(speed), range(range), production(production), cost(cost), unlock(unlock) {}

    Stats(QString type,int attack,int speed,int health,int cost): type(type), attack(attack),
        speed(speed), health(health), cost(cost) {}

    QString getType() { return type; }
    int getAttack() { return attack; }
    int getSpeed() { return speed; }
    int getRange() { return range; }
    int getProduction() { return production; }
    int getHealth() { return health; }
    int getCost() { return cost; }

};

#endif // STATS_H
