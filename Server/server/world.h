#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <QString>
#include <QTextStream>
#include "save.h"
#include "load.h"
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
    QString sendToClient, worldBegin;
    bool sentTeam1, sentTeam2;

    World();

    void readMapFile(QString);
    void readTileInfo(QTextStream&, Tile*);
    void readPaths(QTextStream&);
    void readBuildingFile(QString);
    void readTowerInfo(QTextStream&);
    void readBaseLocation(QTextStream&);
    void readUnitFile(QString);
    void readUnitInfo(QTextStream&);
    void readPlayerFile(QString);
    void upgradeTower(Tile*);


    ~World();

public:

    void setCounter(int init) { counter = init; }
    void buildTower(QString, Tile*);
    Tile* findTileAt(int, int);
    static World* Instance();
    Building& getBuildingType(QString);
    Unit& getUnitType(QString);
    vector<Tile*> getPath(int team);
    QString getSendToClient();
    QString getBeginWorld();
    Tile* getNextPathTile(unsigned int, int);
    void loadUnit(QString type, int team, int x, int y, int direction);
    void updateMoney(int team, int money);

    bool hasSentTeams() {return (sentTeam1 && sentTeam2);}
    void removeTeam(int);

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
    int getRows() {return rows;}
    int getColumns() {return columns;}
    Tile* getTile(int y, int x) {return map[y][x];}
    int getCounter() {return counter;}
    vector<Unit*> getLivingUnits() {return livingUnits;}
    void setSendToClient(QString init) { sendToClient = init; }

    static void Reset();
};


#endif // WORLD_H
