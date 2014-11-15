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
    for (unsigned int i = 0; i < unitTypes.size(); ++i) {
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
    return sendToClient +"\n";
}

QString World::getBeginWorld()
{

    if (!sentTeam1) {
        sentTeam1 = true;
        return "00 1%%" + worldBegin + "\n";
    } else if (!sentTeam2){
        sentTeam2 = true;
        return "00 2%%" + worldBegin + "\n";
    }
    return worldBegin;
}

void World::removeTeam(int team)
{
    if (team == 1) {
        sentTeam1 = false;
    } else if (team == 2){
        sentTeam2 = false;
    }
}

void World::cheatMode(QStringList data)
{
    Player* player = getPlayer(data.at(1).toInt());
    if (data.at(2).toInt() == 1) {
          player->setCheatMode(true);
    } else {
          player->setCheatMode(false);
    }

}

void World::setTimerBtn(int timer)
{
    sendToClient = "40 " + QString::number(timer) + "%%";
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
    unit->setId(nextID);
    ++nextID;
    if(nextID == 1000) { nextID = 0;}
    vector<Tile*> path = getPath(team);
    unit->setXCoord(path[0]->getXCoord());
    unit->setYCoord(path[0]->getYCoord());
    unit->setTeam(team);
    unit->setEndOfPath(false);
    calculateDirection(unit);
    livingUnits.push_back(unit);
    sendToClient += QString("31 ") + QString::number(unit->getID()) + " "
            + unit->getType() + " " + QString::number(unit->getXCoord()) + " "
            + QString::number(unit->getYCoord()) + " " + QString::number(unit->getDirection()) + "%%";

}

void World::loadUnit(QString type, int team, int x, int y, int direction, int indexofpath)
{
    Unit* unit = new Unit(getUnitType(type));
    unit->setXCoord(x);
    unit->setYCoord(y);
    unit->setTeam(team);
    unit->setDirection(direction);
    unit->setIndexOfPath(indexofpath);
    unit->setEndOfPath(false);
    livingUnits.push_back(unit);
    sendToClient += QString("31 ") + QString::number(unit->getID()) + " "
            + unit->getType() + " " + QString::number(unit->getXCoord()) + " "
            + QString::number(unit->getYCoord()) + " " + QString::number(unit->getDirection()) + "%%";
}

void World::updateMoney(int team, int money)
{
    sendToClient += QString("16 ") + QString::number(team) + " " + QString::number(money) + " %%";
}

void World::updateHealth(int team, int health)
{
    sendToClient += QString("14 ") + QString::number(team) + " " + QString::number(health) + "%%";
}

Player* World::getPlayer(int team)
{
    return players[team-1];
}

void World::loadPlayer(QStringList &data)
{
    getPlayer(data.at(1).toInt())->setMoney(data.at(2).toInt());
    getPlayer(data.at(1).toInt())->setHealth(data.at(3).toInt());

    sendToClient += QString("14 ") + data.at(1) + " " + data.at(3) + "%%";

    sendToClient += QString("16 ") + data.at(1) + " " + data.at(2) + "%%";
}

void World::gameOver(int team)
{
    if (gameEnded != true)
    {
        sendToClient = QString("100 ") + QString::number(team) + "%%";
        gameEnded = true;
    }
}

Tile* World::findTileAt(int xCoord, int yCoord)
{
    bool found = false;
    Tile* tile;
    for (int i = 0; i < rows && !found; ++i) {
        for (int j = 0; j < columns && !found; ++j) {
            tile = map[i][j];
            if(tile->getXCoord() == xCoord && tile->getYCoord() == yCoord) { found = true; }
            if (found == true) { return tile; }
        }
    }
    return NULL;
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
    if (counter == 0) {
        counter = 50;
        World::Instance()->deployUnit("2_0" + QString::number(World::Instance()->getPlayer(1)->getUnlockedUnits().at(0)), 1);
        World::Instance()->deployUnit("2_0" + QString::number(World::Instance()->getPlayer(2)->getUnlockedUnits().at(0)), 2);
    } else {
        --counter;
    }
    for(unsigned int i = 0; i < livingUnits.size(); ++i)
    {
        bool finished = false;
        Unit* unit = livingUnits[i];
        updateUnit(unit, finished);
        if (finished) {
            livingUnits.erase(livingUnits.begin() + i);
        }
    }
    /*
    for(int i = 0; i < rows; ++i) {
        for(int j = 0; j < columns; ++j) {
            if (map[i][j]->isBuildable() && map[i][j]->getBuilding() != nullptr) {
                updateTower(map[i][j]->getBuilding());
            }
        }
    }
    */
}

void World::updateUnit(Unit* unit, bool &finished)
{
    //deletes unit when it reaches base
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
    if (unit->getEndOfPath()) {
        if (unit->getTeam() == 1) {
            getPlayer(2)->setHealth(getPlayer(2)->getHealth() - unit->getDamage()); //hurt health
            World::Instance()->updateHealth(getPlayer(2)->getTeam(), getPlayer(2)->getHealth()); //update player info
        }
        if (unit->getTeam() == 2) {
            getPlayer(1)->setHealth(getPlayer(1)->getHealth() - unit->getDamage()); //hurt health
            World::Instance()->updateHealth(getPlayer(1)->getTeam(), getPlayer(1)->getHealth()); //update player info
        }
        if (getPlayer(1)->getHealth() <= 0) { //Move this?
            gameOver(1);
        }
        if (getPlayer(2)->getHealth() <= 0) {
            gameOver(2);
        }
        delete unit;
        finished = true;
        sendToClient += QString("30 ") + QString::number(unit->getID()) + "%%"; //delete unit in client
    }
}

void World::moveNorth(Unit* unit, vector<Tile*>& path)
{
    try {
        unit->setYCoord(unit->getYCoord() - unit->getSpeed());
        if (unit->getYCoord() < path.at(unit->getIndexOfPath())->getYCoord()) {
            unit->incrementIndexOfPath();
            if (calculateDirection(unit)) {
                unit->setYCoord(path.at(unit->getIndexOfPath())->getYCoord());
                sendToClient += "33 " + QString::number(unit->getID()) + " " + QString::number(unit->getXCoord()) + " ";
                sendToClient += QString::number(unit->getYCoord()) + " " + QString::number(unit->getDirection()) + "%%";
            } else {
                sendToClient += "32 " + QString::number(unit->getID()) + " " + QString::number(unit->getXCoord()) + " ";
                sendToClient += QString::number(unit->getYCoord()) + "%%";
            }
            path.at(unit->getIndexOfPath() + 1);

        } else {
            sendToClient += "32 " + QString::number(unit->getID()) + " " + QString::number(unit->getXCoord()) + " ";
            sendToClient += QString::number(unit->getYCoord()) + "%%";
        }
    } catch (...) {
        unit->setEndOfPath(true);
    }
}

void World::moveEast(Unit* unit, vector<Tile*>& path)
{
    try {
        unit->setXCoord(unit->getXCoord() + unit->getSpeed());
        if (unit->getXCoord() > path.at(unit->getIndexOfPath())->getXCoord()) {
            unit->incrementIndexOfPath();
            if (calculateDirection(unit)) {
                unit->setXCoord(path.at(unit->getIndexOfPath())->getXCoord());
                sendToClient += "33 " + QString::number(unit->getID()) + " " + QString::number(unit->getXCoord()) + " ";
                sendToClient += QString::number(unit->getYCoord()) + " " + QString::number(unit->getDirection()) + "%%";
            } else {
                sendToClient += "32 " + QString::number(unit->getID()) + " " + QString::number(unit->getXCoord()) + " ";
                sendToClient += QString::number(unit->getYCoord()) + "%%";
            }
        } else {
            sendToClient += "32 " + QString::number(unit->getID()) + " " + QString::number(unit->getXCoord()) + " ";
            sendToClient += QString::number(unit->getYCoord()) + "%%";
        }
    } catch (...) {
        unit->setEndOfPath(true);
    }
}

void World::moveSouth(Unit* unit, vector<Tile*>& path)
{
    try {
        unit->setYCoord(unit->getYCoord() + unit->getSpeed());
        if (unit->getYCoord() > path.at(unit->getIndexOfPath())->getYCoord()) {
            unit->incrementIndexOfPath();
            if (calculateDirection(unit)) {
                unit->setYCoord(path.at(unit->getIndexOfPath())->getYCoord());
                sendToClient += "33 " + QString::number(unit->getID()) + " " + QString::number(unit->getXCoord()) + " ";
                sendToClient += QString::number(unit->getYCoord()) + " " + QString::number(unit->getDirection()) + "%%";
            } else {
                sendToClient += "32 " + QString::number(unit->getID()) + " " + QString::number(unit->getXCoord()) + " ";
                sendToClient += QString::number(unit->getYCoord()) + "%%";
            }
        } else {
            sendToClient += "32 " + QString::number(unit->getID()) + " " + QString::number(unit->getXCoord()) + " ";
            sendToClient += QString::number(unit->getYCoord()) + "%%";
        }
    } catch (...) {
        unit->setEndOfPath(true);
    }
}

void World::moveWest(Unit* unit, vector<Tile*>& path)
{
    try {
        unit->setXCoord(unit->getXCoord() - unit->getSpeed());
        if (unit->getXCoord() < path.at(unit->getIndexOfPath())->getXCoord()) {
            unit->incrementIndexOfPath();
            if (calculateDirection(unit)) {
                unit->setXCoord(path.at(unit->getIndexOfPath())->getXCoord());
                sendToClient += "33 " + QString::number(unit->getID()) + " " + QString::number(unit->getXCoord()) + " ";
                sendToClient += QString::number(unit->getYCoord()) + " " + QString::number(unit->getDirection()) + "%%";
            } else {
                sendToClient += "32 " + QString::number(unit->getID()) + " " + QString::number(unit->getXCoord()) + " ";
                sendToClient += QString::number(unit->getYCoord()) + "%%";
            }
        } else {
            sendToClient += "32 " + QString::number(unit->getID()) + " " + QString::number(unit->getXCoord()) + " ";
            sendToClient += QString::number(unit->getYCoord()) + "%%";
        }
    } catch (...) {
        unit->setEndOfPath(true);
    }
}

void World::updateTower(Building* building)
{
    (void)building;//stub
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
    if (dy < unit->getSpeed() * (-1)) {
        if(unit->getDirection() != 1) {
            unit->setDirection(1);
            return true;
        }
    } else if (dx > unit->getSpeed()) {
        if(unit->getDirection() != 2) {
            unit->setDirection(2);
            return true;
        }
    } else if (dy > unit->getSpeed()) {
        if(unit->getDirection() != 3) {
            unit->setDirection(3);
            return true;
        }
    } else if (dx < unit->getSpeed() * (-1)) {
        if(unit->getDirection() != 4) {
            unit->setDirection(4);
            return true;
        }
    }
    return false;
}

//constructs the initial game state
World::World() : nextID(0), counter(200), sendToClient(""), sentTeam1(false), sentTeam2(false)
{
    QFile worldFile("://textfiles/world.txt");
    if (!worldFile.open(QIODevice::ReadOnly | QIODevice::Text)) { return; }
    QTextStream readWorld(&worldFile);
    QString filetoRead = readWorld.readLine();
    readMapFile("://textfiles/" + filetoRead);
    filetoRead = readWorld.readLine();
    readBuildingFile("://textfiles/" + filetoRead);
    filetoRead = readWorld.readLine();
    readUnitFile("://textfiles/" + filetoRead);
    filetoRead = readWorld.readLine();
    readPlayerFile("://textfiles/" + filetoRead);
}

//reads the initial map state
void World::readMapFile(QString filename)
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

    worldBegin += "01 " + QString::number(columns) + " " + QString::number(rows);
    worldBegin += " " + QString::number(tileWidth) + " " + QString::number(tileHeight) + "%%";
    map = new Tile**[rows];
    for (int i = 0; i < rows; ++i) {
        map[i] = new Tile*[columns];
        for (int j = 0; j < columns; ++j) {
            Tile* tempTile = new Tile();
            readTileInfo(readMap, tempTile);
            map[i][j] = tempTile;
        }
    }
    readPaths(readMap);
    mapFile.close();
}

//reads individual tile info
void World::readTileInfo(QTextStream& readMap, Tile* tile)
{
    QString temp = readMap.readLine();
    QStringList data = temp.split(" ");
    tile->setBuildable(data[0] == "1");
    tile->setXCoord(data.at(1).toInt());
    tile->setYCoord(data.at(2).toInt());
    tile->setTeam(data.at(3).toInt());

    worldBegin += "01 " + QString::number(tileWidth) + " " + QString::number(tileHeight) + " ";
    worldBegin += QString::number(tile->getXCoord()) + " " + QString::number(tile->getYCoord());
    worldBegin += tile->isBuildable() ? " 1 " : " 0 ";
    worldBegin += QString::number(tile->getTeam()) + "%%";
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
void World::readBuildingFile(QString filename)
{
    QFile buildingFile(filename);
    if (!buildingFile.open(QIODevice::ReadOnly | QIODevice::Text)) { return; }
    QTextStream readBuildings(&buildingFile);
    QString temp = readBuildings.readLine();
    for (int i = 0; i < temp.toInt(); ++i) {
        for (int i = 0; i < 5; ++i) {
            readTowerInfo(readBuildings);
        }
    }
    readBaseLocation(readBuildings);
}

//reads individual tower stats
void World::readTowerInfo(QTextStream& readBuildings)
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
        worldBegin += "02 " + tempbuilding.getType() + " " + QString::number(tempbuilding.getAttack()) + " ";
        worldBegin += QString::number(tempbuilding.getSpeed()) + " " + QString::number(tempbuilding.getRange()) + " ";
        worldBegin += QString::number(tempbuilding.getProduction()) + " " + QString::number(tempbuilding.getCost()) + " ";
        for (int i = 0; i < unlock.size(); ++i) {
            if (i != 0) { worldBegin += ","; }
            worldBegin += unlock.at(i);
        }
        worldBegin += "%%";
    }
}

//reads the starting location for base and creates one there
void World::readBaseLocation(QTextStream& readBuildings)
{
    sendToClient = "";
    QString temp = readBuildings.readLine();
    QStringList data = temp.split(" ");
    QStringList basePoint = data[0].split(",");
    buildTower("1_0_1", map[basePoint[1].toInt()][basePoint[0].toInt()]);
    basePoint = data[1].split(",");
    buildTower("1_0_1", map[basePoint[1].toInt()][basePoint[0].toInt()]);
    worldBegin += sendToClient;
    return;
}

//reads the stats of the types of units
void World::readUnitFile(QString filename)
{
    QFile unitFile(filename);
    if (!unitFile.open(QIODevice::ReadOnly | QIODevice::Text)) { return; }
    QTextStream readUnits(&unitFile);
    QString temp = readUnits.readLine();
    for (int i = 0; i < temp.toInt(); ++i) {
        for (int i = 0; i < 5; ++i) {
            readUnitInfo(readUnits);
        }
    }
}

void World::readUnitInfo(QTextStream& readUnits)
{
    QString temp = readUnits.readLine();
    QStringList data =  temp.split(" ");
    Unit tempUnit;

    tempUnit.setType(data[0]);
    tempUnit.setHealth(data[1].toInt());
    tempUnit.setSpeed(data[2].toInt());
    tempUnit.setDamage(data[3].toInt());
    tempUnit.setCost(data[4].toInt());

    unitTypes.push_back(tempUnit);

    worldBegin += "03 " + tempUnit.getType() + " " + QString::number(tempUnit.getHealth());
    worldBegin += " " + QString::number(tempUnit.getSpeed()) + " " + QString::number(tempUnit.getDamage());
    worldBegin += " " + QString::number(tempUnit.getCost()) + "%%";
}

//reads the starting stats of the players
void World::readPlayerFile(QString filename)
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

        worldBegin += "11 " + QString::number(player->getTeam()) + " " + QString::number((player->getHealth()));
        worldBegin += " " + QString::number(player->getMoney()) + " ";
        for (unsigned int i = 0; i < player->getUnlockedBuildings().size(); ++i) {
            int lvl = player->getUnlockedBuildings().at(i);
            if (i != 0) {worldBegin += ",";}
            worldBegin += "1_" + QString::number(i) + "_" + QString::number(lvl);
        }
        for (unsigned int i = 0; i < player->getUnlockedUnits().size(); ++i) {
            int lvl = player->getUnlockedUnits().at(i);
            worldBegin += ",2_" + QString::number(i) + "_" + QString::number(lvl);
        }
        worldBegin += "%%";
    }
}

void World::buildTower(QString type, Tile* tile)
{
    Building* building = new Building(getBuildingType(type));
    tile->placeBuilding(building);

    type.replace(type.length() - 1, 1, type[type.length() - 1].digitValue() + 49);
    Building nextLvlBuilding = Building(getBuildingType(type));

    sendToClient += "21 " + QString::number(tile->getXCoord()) + " " + QString::number(tile->getYCoord());
    sendToClient += " " + building->getType() + " " + QString::number(tile->getTeam()) + " ";
    sendToClient += QString::number(nextLvlBuilding.getAttack()) + " " + QString::number(nextLvlBuilding.getSpeed()) + " ";
    sendToClient += QString::number(nextLvlBuilding.getRange()) + " " + QString::number(nextLvlBuilding.getProduction());
    sendToClient += " " + QString::number(nextLvlBuilding.getCost()) + " ";
    for (int i = 0; i < nextLvlBuilding.getUnlock().size(); ++i) {
        if (i != 0) { sendToClient += ","; }
        sendToClient += nextLvlBuilding.getUnlock().at(i);
    }
    sendToClient += "%%";
}

void World::buyTower(QStringList& data)
{
    Tile* tile = findTileAt(data.at(2).toInt(), data.at(3).toInt());
    int cost = getBuildingType(data.at(1)).getCost();
    if (getPlayer(tile->getTeam())->attemptToSpendMoney(cost)) {
        buildTower(data.at(1), tile);
        tile->getBuilding()->addtoTotalCost();
    }
}

void World::buyUnit(QStringList& data)
{
    int cost = getUnitType(data[1]).getCost();
    if (getPlayer(data[2].toInt())->attemptToSpendMoney(cost)) {
        QString type = QString(data.at(1));
        int team = data.at(2).toInt();
        deployUnit(type, team);
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
    Load *load = new Load(filename);

    delete load;
}

void World::save(QString filename)
{
    Save *save = new Save(filename);

    delete save;

}

void World::Reset()
{
    delete world;
    world = new World();
}
