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
Building& World::getBuildingType(QString type)
{
    for (unsigned int i = 0; i < buildingTypes.size(); ++i) {
        if(buildingTypes.at(i).getType() == type) {
            return buildingTypes[i];
        }
    }
    return buildingTypes.at(0);
}

//returns a copy of the unit type
Unit& World::getUnitType(QString type)
{
    for (unsigned int i = 0; i < buildingTypes.size(); ++i) {
        if(unitTypes.at(i).getType() == type) {
            return unitTypes[i];
        }
    }
    return unitTypes.at(0);
}

//return the path the units must travel
vector<Tile*> World::getPath(int team)
{
    if(team == 1) {return team1path;}
    else {return team2path;}
}

QString World::getSendToClient()
{
    if (!sentTeam1) {
        sendToClient = "00 1%%" + sendToClient;
        sentTeam1 = true;
    } else if (!sentTeam2){
        sendToClient = "00 2%%" + sendToClient;
        sentTeam2 = true;
    }
    return sendToClient;
}

//increases calls the upgrade method of the building and passes the info to use
void World::upgradeTower(Tile* tile)
{
    Building* building = tile->getBuilding();
    building->upgrade(getBuildingType(building->getType()));
}

//deploys a unit of specified type on specified team
void World::deployUnit(QString type, int team)
{
    Unit* unit = new Unit(getUnitType(type));
    vector<Tile*> path = getPath(team);
    unit->setXCoord(path[0]->getXCoord());
    unit->setYCoord(path[0]->getYCoord());
    unit->setTeam(team);
    calculateDirection(unit);
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

World::~World()
{
    for(int y = 0; y < world->rows; ++y)
    {
        for(int x = 0; x < world->columns; ++x)
        {
            delete world->map[y][x];
        }
    }
    delete world->map;

    delete world->players[0];
    delete world->players[1];
    world->players.clear();

    for (unsigned int i = 0; i < livingUnits.size(); ++i) {
        delete world->livingUnits.at(i);
    }
    world->livingUnits.clear();

    for (unsigned int i = 0; i < team1path.size(); ++i) {
        delete world->team1path.at(i);
    }
    world->team1path.clear();

    for (unsigned int i = 0; i < team2path.size(); ++i) {
        delete world->team2path.at(i);
    }
    world->team2path.clear();
}

//runs every 20 milliseconds
void World::updateWorld()
{
    sendToClient = "";
    for(unsigned int i = 0; i < livingUnits.size(); ++i)
    {
        updateState(livingUnits[i]);
    }
    for(int i = 0; i < rows; ++i) {
        for(int j = 0; j < columns; ++j) {
            if (map[i][j]->isBuildable() && map[i][j]->getBuilding() != nullptr) {
                updateState(map[i][j]->getBuilding());
            }
        }
    }
}

void World::updateState(Unit* unit)
{
    int direction = unit->getDirection();
    vector<Tile*> path = getPath(unit->getTeam());
    if (direction == 1) {
        moveNorth(unit, path);
    } else if (direction == 2) {
        moveEast(unit, path);
    } else if (direction == 3) {
        moveSouth(unit, path);
    } else if (direction == 4) {
        moveWest(unit, path);
    }
}

void World::moveNorth(Unit* unit, vector<Tile*>& path)
{
    unit->setYCoord(unit->getYCoord() + unit->getSpeed());
    if (unit->getYCoord() > path.at(unit->getIndexOfPath())->getYCoord()) {
        if (calculateDirection(unit)) {
            unit->setYCoord(path.at(unit->getIndexOfPath())->getYCoord());
            sendToClient += "33 " + QString::number(unit->getID()) + " " + QString::number(unit->getXCoord()) + " ";
            sendToClient += QString::number(unit->getYCoord()) + " 1%%";
        } else {
            sendToClient += "32 " + QString::number(unit->getID()) + " " + QString::number(unit->getXCoord()) + " ";
            sendToClient += QString::number(unit->getYCoord()) + "%%";
        }
        unit->incrementIndexOfPath();
        unit->setEndOfPath(path.at(unit->getIndexOfPath()));
    }
}

void World::moveEast(Unit* unit, vector<Tile*>& path)
{
    unit->setXCoord(unit->getXCoord() + unit->getSpeed());
    if (unit->getXCoord() > path.at(unit->getIndexOfPath())->getXCoord()) {
        if (calculateDirection(unit)) {
            unit->setXCoord(path.at(unit->getIndexOfPath())->getYCoord());
            sendToClient += "33 " + QString::number(unit->getID()) + " " + QString::number(unit->getXCoord()) + " ";
            sendToClient += QString::number(unit->getYCoord()) + " 2%%";
        } else {
            sendToClient += "32 " + QString::number(unit->getID()) + " " + QString::number(unit->getXCoord()) + " ";
            sendToClient += QString::number(unit->getYCoord()) + "%%";
        }
        unit->incrementIndexOfPath();
        unit->setEndOfPath(path.at(unit->getIndexOfPath()));
    }
}

void World::moveSouth(Unit* unit, vector<Tile*>& path)
{
    unit->setYCoord(unit->getYCoord() - unit->getSpeed());
    if (unit->getYCoord() < path.at(unit->getIndexOfPath())->getYCoord()) {
        if (calculateDirection(unit)) {
            unit->setYCoord(path.at(unit->getIndexOfPath())->getYCoord());
            sendToClient += "33 " + QString::number(unit->getID()) + " " + QString::number(unit->getXCoord()) + " ";
            sendToClient += QString::number(unit->getYCoord()) + " 3%%";
        } else {
            sendToClient += "32 " + QString::number(unit->getID()) + " " + QString::number(unit->getXCoord()) + " ";
            sendToClient += QString::number(unit->getYCoord()) + "%%";
        }
        unit->incrementIndexOfPath();
        unit->setEndOfPath(path.at(unit->getIndexOfPath()));
    }
}

void World::moveWest(Unit* unit, vector<Tile*>& path)
{
    unit->setXCoord(unit->getXCoord() - unit->getSpeed());
    if (unit->getXCoord() < path.at(unit->getIndexOfPath())->getXCoord()) {
        if (calculateDirection(unit)) {
            unit->setXCoord(path.at(unit->getIndexOfPath())->getYCoord());
            sendToClient += "33 " + QString::number(unit->getID()) + " " + QString::number(unit->getXCoord()) + " ";
            sendToClient += QString::number(unit->getYCoord()) + " 4%%";
        } else {
            sendToClient += "32 " + QString::number(unit->getID()) + " " + QString::number(unit->getXCoord()) + " ";
            sendToClient += QString::number(unit->getYCoord()) + "%%";
        }
        unit->incrementIndexOfPath();
        unit->setEndOfPath(path.at(unit->getIndexOfPath()));
    }
}

void World::updateState(Building* building)
{
    (void)building;//stub
}

//checks to see whether this interval is the one to deploy
void World::canDeployUnits()
{
    if (counter == 0)
    {
        for(int i = 1; i < players[0]->getUnitCuesSize(); ++i) {
            if (players[0]->checkUnitCue(i)) {
                QString type = "2_" + QString::number(i/5) + "_" + QString::number(i%5);
                deployUnit(type, 1);
            }
        }
        counter = 150;
    } else { --counter; }
}

bool World::calculateDirection(Unit* unit)
{
    Tile* tile;
    if (unit->getTeam() == 1) {
        tile = team1path.at(unit->getIndexOfPath());
    } else if (unit->getTeam() == 2) {
        tile = team2path.at(unit->getIndexOfPath());
    }
    int dy = tile->getYCoord()-unit->getYCoord();
    int dx = tile->getXCoord()-unit->getXCoord();
    if (dy > 0) {
        if(unit->getDirection() != 1) {
            unit->setDirection(1);
            return true;
        }
    } else if (dx > 0) {
        if(unit->getDirection() != 2) {
            unit->setDirection(2);
            return true;
        }
    } else if (dy < 0) {
        if(unit->getDirection() != 3) {
            unit->setDirection(3);
            return true;
        }
    } else if (dx < 0) {
        if(unit->getDirection() != 4) {
            unit->setDirection(4);
            return true;
        }
    }
    return false;
}

//constructs the initial game state
World::World() : counter(500), sentTeam1(false), sentTeam2(false)
{
    QFile worldFile("://textfiles/world.txt");
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

    sendtoClient += "01 " + QString::number(columns) + " " + QString::number(rows);
    sendtoClient += " " + QString::number(tileWidth) + " " + QString::number(tileHeight) + "%%";
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
    tile->setXCoord(data.at(1).toInt());
    tile->setYCoord(data.at(2).toInt());
    tile->setTeam(data.at(3).toInt());

    sendtoClient += "01 " + QString::number(tileWidth) + " " + QString::number(tileHeight) + " ";
    sendtoClient += QString::number(tile->getXCoord()) + " " + QString::number(tile->getYCoord());
    sendtoClient += tile->isBuildable() ? " 1 " : " 0 ";
    sendtoClient += QString::number(tile->getTeam()) + "%%";
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

    tempbuilding.setType(data[0]);
    tempbuilding.setAttack(data[1].toInt());
    tempbuilding.setProduction(data[2].toInt());
    tempbuilding.setRange(data[3].toInt());
    tempbuilding.setSpeed(data[4].toInt());

    QStringList unlock;
    if (data[5] != "0")
    {
        unlock = data[5].split(",");
        tempbuilding.setUnlock(unlock);
    }
    tempbuilding.setCost(data[6].toInt());
    buildingTypes.push_back(tempbuilding);

    if (tempbuilding.getType().split("_").at(2) == "1") {
        sendtoClient += "02 " + tempbuilding.getType() + " " + QString::number(tempbuilding.getAttack()) + " ";
        sendtoClient += QString::number(tempbuilding.getSpeed()) + " " + QString::number(tempbuilding.getRange()) + " ";
        sendtoClient += QString::number(tempbuilding.getProduction()) + " " + QString::number(tempbuilding.getCost()) + " ";
        for (int i = 0; i < unlock.size(); ++i) {
            if (i != 0) { sendtoClient += ","; }
            sendtoClient += unlock.at(i);
        }
        sendtoClient += "%%";
    }
}

//reads the starting location for base and creates one there
void World::readBaseLocation(QTextStream& readBuildings, QString& sendtoClient)
{
    QString temp = readBuildings.readLine();
    QStringList data = temp.split(" ");
    QStringList basePoint = data[0].split(",");
    buildTower("1_0_1", map[basePoint[1].toInt()][basePoint[0].toInt()], sendtoClient);
    basePoint = data[1].split(",");
    buildTower("1_0_1", map[basePoint[1].toInt()][basePoint[0].toInt()], sendtoClient);
    return;
}

//reads the stats of the types of units
void World::readUnitFile(QString filename, QString& sendtoClient)
{
    QFile unitFile(filename);
    if (!unitFile.open(QIODevice::ReadOnly | QIODevice::Text)) { return; }
    QTextStream readUnits(&unitFile);
    QString temp = readUnits.readLine();
    for (int i = 0; i < temp.toInt(); ++i) {
        for (int i = 0; i < 5; ++i) {
            readUnitInfo(readUnits, sendtoClient);
        }
    }
}

void World::readUnitInfo(QTextStream& readUnits, QString& sendtoClient)
{
    QString temp = readUnits.readLine();
    QStringList data =  temp.split(" ");
    Unit tempUnit(true);

    tempUnit.setType(data[0]);
    tempUnit.setHealth(data[1].toInt());
    tempUnit.setSpeed(data[2].toInt());
    tempUnit.setDamage(data[3].toInt());
    tempUnit.setCost(data[4].toInt());

    unitTypes.push_back(tempUnit);

    sendtoClient += "03 " + tempUnit.getType() + " " + QString::number(tempUnit.getHealth());
    sendtoClient += " " + QString::number(tempUnit.getSpeed()) + " " + QString::number(tempUnit.getDamage());
    sendtoClient += " " + QString::number(tempUnit.getCost()) + "%%";
}

//reads the starting stats of the players
void World::readPlayerFile(QString filename, QString& sendtoClient)
{
    QFile playerFile(filename);
    if (!playerFile.open(QIODevice::ReadOnly | QIODevice::Text)) { return; }
    QTextStream readPlayerInfo(&playerFile);
    for (int i = 1; i < 3; ++i) {
        QString temp = readPlayerInfo.readLine();
        QStringList info = temp.split(" ");
        Player* player = new Player(info[0].toInt(), info[1].toInt(), i);
        player->setInitialUnlocks(buildingTypes, unitTypes);
        players.push_back(player);

        sendtoClient += "11 " + QString::number(player->getTeam()) + " " + QString::number((player->getHealth()));
        sendtoClient += " " + QString::number(player->getMoney()) + " ";
        for (unsigned int i = 0; i < player->getUnlockedBuildings().size(); ++i) {
            int lvl = player->getUnlockedBuildings().at(i);
            if (i != 0) {sendtoClient += ",";}
            sendtoClient += "1_" + QString::number(i) + "_" + QString::number(lvl);
        }
        for (unsigned int i = 0; i < player->getUnlockedUnits().size(); ++i) {
            int lvl = player->getUnlockedUnits().at(i);
            sendtoClient += ",2_" + QString::number(i) + "_" + QString::number(lvl);
        }
        sendtoClient += "%%";
    }
}

void World::buildTower(QString type, Tile* tile, QString& sendtoClient)
{
    Building* building = new Building(getBuildingType(type));
    tile->placeBuilding(building);

    type.replace(type.length() - 1, 1, type[type.length() - 1].digitValue() + 49);
    Building nextLvlBuilding = Building(getBuildingType(type));

    sendtoClient += "21 " + QString::number(tile->getXCoord()) + " " + QString::number(tile->getYCoord());
    sendtoClient += " " + building->getType() + " " + QString::number(tile->getTeam()) + " ";
    sendtoClient += QString::number(nextLvlBuilding.getAttack()) + " " + QString::number(nextLvlBuilding.getSpeed()) + " ";
    sendtoClient += QString::number(nextLvlBuilding.getRange()) + " " + QString::number(nextLvlBuilding.getProduction());
    sendtoClient += " " + QString::number(nextLvlBuilding.getCost()) + " ";
    for (int i = 0; i < nextLvlBuilding.getUnlock().size(); ++i) {
        if (i != 0) { sendtoClient += ","; }
        sendtoClient += nextLvlBuilding.getUnlock().at(i);
    }
    sendtoClient += "%%";
}

void World::buyTower(QStringList& data)
{
    sendToClient = "";
    Tile* tile = findTileAt(data.at(2).toInt(), data.at(3).toInt());
    int cost = getBuildingType(data.at(1)).getCost();
    if (getPlayer(tile->getTeam())->attempttoSpendMoney(cost)) {
        buildTower(data.at(1), tile, sendToClient);
    }
    tile->getBuilding()->addtoTotalCost();

}

void World::buyUnit(QStringList& data)
{
    int cost = getUnitType(data[1]).getCost();
    if (getPlayer(data[2].toInt())->attempttoSpendMoney(cost)) {
        deployUnit(data.at(1), data.at(2).toInt());
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
    Building upgrade = getBuildingType(tile->getBuilding()->getType());
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

void World::Reset()
{
    delete world;
    world = new World();
}
