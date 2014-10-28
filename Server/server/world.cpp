#include "world.h"
#include <QFile>
#include <QStringList>

using namespace std;

// Global static pointer used to ensure a single instance of the class.
World* World::world = NULL;

//returns the instance of the world and if there is none creates it
World* World::Instance()
{
    if(!world) {
        world = new World();
    }
    return world;
}

//returns a copy of the building type
Building& World::getBuildingType(int type, int level)
{
    int towerIndex = type*5 + level - 1;
    return buildingTypes[towerIndex];
}

//returns a copy of the unit type
Unit& World::getUnitType(int type, int level)
{
    int unitIndex = type*5 + level - 1;
    return unitTypes[unitIndex];
}

//return the path the units must travel
vector<Tile*>& World::getPath(int team)
{
    if(team == 1) {return team1path;}
    else {return team2path;}
}

//increases calls the upgrade method of the building and passes the info to use
void World::upgradeTower(Tile* tile)
{
    Building* building = tile->getBuilding();
    building->upgrade(getBuildingType(building->getType(), building->getLevel() + 1));
}

//deploys a unit of specified type on specified team
void World::deployUnit(int type, int team)
{
    Unit* unit = new Unit(getUnitType(type, players[team]->checkLevelofUnit(type)));
    vector<Tile*> path = getPath(team);
    unit->setXCoord(path[0]->getXCoord());
    unit->setYCoord(path[0]->getYCoord());
    unit->setTeam(team);
    livingUnits.push_back(unit);
}

Player* World::getPlayer(int team)
{
    return players[team-1];
}

Tile* World::findTileAt(int xCoord, int yCoord)
{
    bool found = false;
    Tile* tile;
    for (int i = 0; i < rows && !found; ++i) {
        for (int j = 0; j < columns && !found; ++j) {
            tile = map[i][j];
            if(tile->getXCoord() == xCoord && tile->getYCoord() == yCoord) { found = true; }
        }
    }
    return tile;
}

//runs every 20 milliseconds
void World::updateWorld()
{
    for(unsigned int i = 0; i < livingUnits.size(); ++i)
    {
        livingUnits[i]->updateState();
    }
    for(int i = 0; i < rows; ++i) {
        for(int j = 0; j < columns; ++j) {
            if (map[i][j]->isBuildable() && map[i][j]->getBuilding() != nullptr) {
                map[i][j]->getBuilding()->updateState();
            }
        }
    }
}

//checks to see whether this interval is the one to deploy
void World::canDeployUnits()
{
    if (counter == 0)
    {
        for(int i = 1; i < players[0]->getUnitCuesSize(); ++i) {
            if (players[0]->checkUnitCue(i)) {
                deployUnit(i, 1);
            }
        }
        counter = 150;
    } else { --counter; }
}

//constructs the initial game state
World::World() : counter(500)
{
    QString sendToClient = "";
    QFile worldFile("world.txt");
    if (!worldFile.open(QIODevice::ReadOnly | QIODevice::Text)) { return; }
    QTextStream readWorld(&worldFile);
    QString filetoRead = readWorld.readLine();
    readMapFile("://textfiles/" + filetoRead, sendToClient);
    filetoRead = readWorld.readLine();
    readBuildingFile("://textfiles/" + filetoRead, sendToClient);
    filetoRead = readWorld.readLine();
    readUnitFile("://textfiles/" + filetoRead, sendToClient);
    filetoRead = readWorld.readLine();
    readPlayerFile("://textfiles/" + filetoRead, sendToClient);
    sendWorldStartInfotoClients();
}

//reads the initial map state
void World::readMapFile(QString filename, QString& sendtoClient)
{

    QFile mapFile(filename);
    if (!mapFile.open(QIODevice::ReadOnly | QIODevice::Text)) { return; }
    QTextStream readMap(&mapFile);
    QString temp = readMap.readLine();
    rows = temp.toInt();
    temp = readMap.readLine();
    columns = temp.toInt();
    temp = readMap.readLine();
    QStringList dimensions = temp.split("x");
    tileWidth = dimensions[0].toInt();
    tileHeight = dimensions[1].toInt();

    map = new Tile**[rows];
    for (int i = 0; i < rows; ++i) {
        map[i] = new Tile*[columns];
        for (int j = 0; j < columns; ++j) {
            Tile* tempTile = new Tile();
            readTileInfo(readMap, tempTile, sendtoClient);
            map[i][j] = tempTile;
        }
    }
    readPaths(readMap);
    mapFile.close();
}

//reads individual tile info
void World::readTileInfo(QTextStream& readMap, Tile* tile, QString& sendtoClient)
{
    QString temp = readMap.readLine();
    QStringList data = temp.split(" ");
    tile->setBuildable(data[0] == "1");
    tile->setXCoord(data[1].toInt());
    tile->setYCoord(data[2].toInt());
    tile->setTeam(data[3].toInt());

    sendtoClient += "01 " + QString::number(tileWidth) + " " + QString::number(tileHeight) + " ";
    sendtoClient += QString::number(tile->getXCoord()) + " " + QString::number(tile->getXCoord());
    sendtoClient += " " + tile->isBuildable() ? "1 " : "0 ";
    sendtoClient += QString::number(tile->getTeam()) + "/n";
}

//reads what paths the units will use
void World::readPaths(QTextStream& readMap)
{
    QString temp = readMap.readLine();
    QStringList data = temp.split(" ");
    for (int i = 0; i < data.length(); ++i) {
        QStringList point = data[i].split(",");
        Tile* tile = map[point[1].toInt()][point[0].toInt()];
        team1path.push_back(tile);
    }
    temp = readMap.readLine();
    data = temp.split(" ");
    for (int i = 0; i < data.length(); ++i) {
        QStringList point = data[i].split(",");
        Tile* tile = map[point[1].toInt()][point[0].toInt()];
        team2path.push_back(tile);
    }
}

//reads the stats of the types of towers
void World::readBuildingFile(QString filename, QString& sendtoClient)
{
    QFile buildingFile(filename);
    if (!buildingFile.open(QIODevice::ReadOnly | QIODevice::Text)) { return; }
    QTextStream readBuildings(&buildingFile);
    QString temp = readBuildings.readLine();
    for (int i = 0; i < temp.toInt(); ++i) {
        for (int i = 0; i < 5; ++i) {
            readTowerInfo(readBuildings, sendtoClient);
        }
    }
    readBaseLocation(readBuildings, sendtoClient);
}

//reads individual tower stats
void World::readTowerInfo(QTextStream& readBuildings, QString& sendtoClient)
{
    QString temp = readBuildings.readLine();
    QStringList data = temp.split(" ");
    Building tempbuilding;

    tempbuilding.setType(data[0].toInt());
    tempbuilding.setLevel(data[1].toInt());
    tempbuilding.setAttack(data[2].toInt());
    tempbuilding.setProduction(data[3].toInt());
    tempbuilding.setRange(data[4].toInt());
    tempbuilding.setSpeed(data[5].toInt());

    if (data[6] != "0")
    {
        QStringList tempunlocks = data[6].split(",");
        vector<int> unlocks;
        for(int i = 0; i < tempunlocks.length(); ++i) {
            unlocks.push_back(tempunlocks[i].toInt());
        }
        tempbuilding.setUnlock(unlocks);
    }
    tempbuilding.setCost(data[7].toInt());
    buildingTypes.push_back(tempbuilding);

    sendtoClient += "02 1_" + QString::number(tempbuilding.getType()) + "_" + QString::number(tempbuilding.getLevel());
    sendtoClient += " " + QString::number(tempbuilding.getAttack()) + " " + QString::number(tempbuilding.getSpeed());
    sendtoClient += " " + QString::number(tempbuilding.getRange()) + " " + QString::number(tempbuilding.getProduction());
    sendtoClient += " " + QString::number(tempbuilding.getCost());
}

//reads the starting location for base and creates one there
void World::readBaseLocation(QTextStream& readBuildings, QString& sendtoClient)
{
    QString temp = readBuildings.readLine();
    QStringList data = temp.split(" ");
    QStringList basePoint = data[0].split(",");
    buildTower(10, map[basePoint[1].toInt()][basePoint[0].toInt()]);
}

//reads the stats of the types of units
void World::readUnitFile(QString filename, QString& sendtoClient)
{
    QFile unitFile(filename);
    if (!unitFile.open(QIODevice::ReadOnly | QIODevice::Text)) { return; }
    QTextStream readUnits(&unitFile);


}

//reads the starting stats of the players
void World::readPlayerFile(QString filename, QString& sendtoClient)
{
    QFile playerFile(filename);
    if (!playerFile.open(QIODevice::ReadOnly | QIODevice::Text)) { return; }
    QTextStream readPlayerInfo(&playerFile);
    QString temp = readPlayerInfo.readLine();
    QStringList info = temp.split(" ");
    Player* player = new Player(info[0].toInt(), info[1].toInt(), 1);
    player->setInitialUnlocks(buildingTypes, unitTypes);
    players.push_back(player);
    temp = readPlayerInfo.readLine();
    info = temp.split(" ");
    player = new Player(info[0].toInt(), info[1].toInt(), 1);
    player->setInitialUnlocks(buildingTypes, unitTypes);
    players.push_back(player);
}

void World::buildTower(int type, Tile* tile)
{
    Building* building = new Building(getBuildingType(type, 1));
    tile->placeBuilding(building);
}

//self explanatory
void World::sendWorldStartInfotoClients()
{

}

void World::buyTower(QStringList& data)
{
    Tile* tile = findTileAt(data.at(2).toInt(), data.at(3).toInt());
    int cost = getBuildingType(data.at(1).toInt(), 1).getCost();
    if (getPlayer(tile->getTeam())->attempttoSpendMoney(cost)) {
        buildTower(data.at(1).toInt(), tile);
    }
    tile->getBuilding()->addtoTotalCost();

    //stub
}

void World::buyUnit(QStringList& data)
{
    int cost = getUnitType(data[1].toInt(), 1).getCost();
    if (getPlayer(data[2].toInt())->attempttoSpendMoney(cost)) {
        deployUnit(data.at(1).toInt(), data.at(2).toInt());
    }
}

void World::destroy(QStringList& data)
{
    findTileAt(data.at(1).toInt(),data.at(2).toInt())->destroyBuilding();

    //stub
}

void World::upgrade(QStringList& data)
{
    Tile* tile = findTileAt(data.at(1).toInt(),data.at(2).toInt());
    Building upgrade = getBuildingType(tile->getBuilding()->getType(),tile->getBuilding()->getLevel() + 1);
    tile->upgradeBuilding(upgrade);
}

void World::load(QString filename)
{
    (void)filename;//stub
}

void World::save(QString filename)
{
    (void)filename;//stub
}
