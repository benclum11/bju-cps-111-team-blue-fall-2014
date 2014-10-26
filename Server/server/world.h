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
    World(vector<QString> filenames);

    void readMapFile(QString);
    void readTileInfo(QTextStream&, Tile*);
    void readPaths(QTextStream&);
    void readTowerFile(QString);
    void readTowerInfo(QTextStream&);
    void readBaseLocation(QTextStream&);
    void readUnitFile(QString);
    void readPlayerFile(QString);

    void sendWorldStartInfotoClient();

public:

    static World* Instance();
    Building& getBuildingType(int, int);
    Unit& getUnitType(int, int);

    vector<Tile*>& getPath(int team);

    void buildTower(int,Tile*);
    void upgradeTower(Tile*);
    void deployUnit(int,int);

    void updateWorld();

    void canDeployUnits();
};


#endif // WORLD_H
