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
    int nextID;
    int counter, rows, columns, tileWidth, tileHeight;
    QString sendToClient, worldBegin;
    bool sentTeam1, sentTeam2, gameEnded;

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
    void removeTeam(int);

    void cheatMode(QStringList);

    Tile* findTileAt(int, int);
    static World* Instance();


    void loadUnit(QString type, int team, int x, int y, int direction);
    void updateMoney(int, int);
    void updateHealth(int, int);
    Building& getBuildingType(QString); //returns building based on type

    bool hasSentTeams() {return (sentTeam1 && sentTeam2);}


    Player* getPlayer(int);
    void loadPlayer(QStringList &data);
    void gameOver(int team);

    void updateWorld();
    void updateUnit(Unit*, bool&);
    void moveNorth(Unit*, vector<Tile*>&);
    void moveEast(Unit*, vector<Tile*>&);
    void moveSouth(Unit*, vector<Tile*>&);
    void moveWest(Unit*, vector<Tile*>&);

    void updateTower(Building*);

    bool calculateDirection(Unit*);

    void buyTower(QStringList&);
    void buyUnit(QStringList&);
    void deployUnit(QString,int);
    void destroy(QStringList&);
    void upgrade(QStringList&);
    void load(QString);
    void save(QString);


    static void Reset();

    //getter methods

    Unit& getUnitType(QString);
    vector<Tile*> getPath(int team);
    QString getSendToClient();
    QString getBeginWorld();
    Tile* getNextPathTile(unsigned int, int);
    int getRows() {return rows;}
    int getColumns() {return columns;}
    Tile* getTile(int y, int x) {return map[y][x];}
    int getCounter() {return counter;}
    vector<Unit*> getLivingUnits() {return livingUnits;}
};


#endif // WORLD_H
