#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <QString>
#include <QTextStream>
#include "building.h"
#include "unit.h"
#include "tile.h"
#include "player.h"

using namespace std;

class World {

    static World* world;
    vector<Unit> unitTypes;
    vector<Building> buildingTypes;
    Tile*** map;
    vector<Object*> object;
    vector<Tile*> team1path, team2path;
    vector<Player*> players;
    vector<Unit*> livingUnits;
    int counter, rows, columns, tileWidth, tileHeight;
    QString sendToClient;

    World();

    void readMapFile(QString, QString&);
    void readTileInfo(QTextStream&, Tile*, QString&);
    void readPaths(QTextStream&);
    void readBuildingFile(QString, QString&);
    void readTowerInfo(QTextStream&, QString&);
    void readBaseLocation(QTextStream&, QString&);
    void readUnitFile(QString, QString&);
    void readUnitInfo(QTextStream&, QString&);
    void readPlayerFile(QString, QString&);

    void buildTower(QString, Tile*, QString&);
    void upgradeTower(Tile*);
    void deployUnit(QString,int);
    Player* getPlayer(int);

    Tile* findTileAt(int, int);

public:

    static World* Instance();
    Building& getBuildingType(QString);
    Unit& getUnitType(QString);
    vector<Tile*>& getPath(int team);
    QString getSendToClient() {return sendToClient;}

    void updateWorld();

    void canDeployUnits();

    void buyTower(QStringList&);
    void buyUnit(QStringList&);
    void destroy(QStringList&);
    void upgrade(QStringList&);
    void load(QString);
    void save(QString);
};


#endif // WORLD_H
