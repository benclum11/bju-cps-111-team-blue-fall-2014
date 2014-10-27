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
    int counter, rows, columns;
    vector<int> team1unitCues,team2unitCues;

    World();

    void readMapFile(QString);
    void readTileInfo(QTextStream&, Tile*);
    void readPaths(QTextStream&);
    void readBuildingFile(QString);
    void readTowerInfo(QTextStream&);
    void readBaseLocation(QTextStream&);
    void readUnitFile(QString);
    void readPlayerFile(QString);

    void buildTower(int,Tile*);
    void upgradeTower(Tile*);
    void deployUnit(int,int);

    void findTileAt(int, int);
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
