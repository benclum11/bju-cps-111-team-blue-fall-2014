#ifndef WORLD_H
#define WORLD_H

#include <vector>
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
    int counter;
    vector<int> team1unitCues,team2unitCues;

    World();

    void readMapFile();
    void readTileInfo(QTextStream&, Tile*);
    void readPaths(QTextStream&);
    void readTowerFile();
    void readTowerInfo(QTextStream&);
    void readBaseLocation(QTextStream&);
    void readUnitFile();

public:

    static World* Instance();
    Building getBuildingType(int);
    Unit getUnitType(int);

    void buildTower(int,int,Tile*);
    void deployUnit(int,int);

    void updateWorld();

    void canDeployUnits();

};


#endif // WORLD_H
