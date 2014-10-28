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

    World();

    void readMapFile(QString, QString&);
    void readTileInfo(QTextStream&, Tile*, QString&);
    void readPaths(QTextStream&);
    void readBuildingFile(QString, QString&);
    void readTowerInfo(QTextStream&, QString&);
    void readBaseLocation(QTextStream&, QString&);
    void readUnitFile(QString, QString&);
    void readPlayerFile(QString, QString&);

    void buildTower(int, Tile*);
    void upgradeTower(Tile*);
    void deployUnit(int,int);
    Player* getPlayer(int);

    Tile* findTileAt(int, int);

public:

    static World* Instance();
    Building& getBuildingType(int, int);
    Unit& getUnitType(int, int);

    vector<Tile*>& getPath(int team);

    void updateWorld();

    void canDeployUnits();
    void sendWorldStartInfotoClients();

    void buyTower(QStringList&);
    void buyUnit(QStringList&);
    void destroy(QStringList&);
    void upgrade(QStringList&);
    void load(QString);
    void save(QString);
};


#endif // WORLD_H
