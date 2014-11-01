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
    vector<Tile*> team1path, team2path;
    vector<Player*> players;
    vector<Unit*> livingUnits;
    int counter, rows, columns, tileWidth, tileHeight;
    QString sendToClient;
    bool sentTeam1, sentTeam2;

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
    Tile* findTileAt(int, int);

    ~World();

public:

    static World* Instance();
    Building& getBuildingType(QString);
    Unit& getUnitType(QString);
    vector<Tile*> getPath(int team);
    QString getSendToClient();
    Tile* getNextPathTile(unsigned int, int);

    bool hasSentTeams() {return (sentTeam1 && sentTeam2);}

    Player* getPlayer(int);

    void updateWorld();
    void updateState(Unit*);
    void moveNorth(Unit*, vector<Tile*>&);
    void moveEast(Unit*, vector<Tile*>&);
    void moveSouth(Unit*, vector<Tile*>&);
    void moveWest(Unit*, vector<Tile*>&);

    void updateState(Building*);

    void canDeployUnits();

    bool calculateDirection(Unit*);

    void buyTower(QStringList&);
    void buyUnit(QStringList&);
    void deployUnit(QString,int);
    void destroy(QStringList&);
    void upgrade(QStringList&);
    void load(QString);
    void save(QString);

    static void Reset();
};


#endif // WORLD_H
