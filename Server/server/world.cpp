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
vector<Tile*>& World::getPath(int team)
{
    if(team == 1) {return team1path;}
    else {return team2path;}
}

QString World::getSendToClient()
{
    if (!sentTeams) {
        ++currteam;
        sendToClient = "00 " + QString::number(currteam) + "%%" + sendToClient;
        if(currteam == 2) {sentTeams = true;}
    }
    return sendToClient;
}

void World::removeOnePlayer()
{
    --currteam;
    sentTeams = false;
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
                QString type = "2_" + QString::number(i/5) + "_" + QString::number(i%5);
                deployUnit(type, 1);
            }
        }
        counter = 150;
    } else { --counter; }
}

//constructs the initial game state
World::World() : counter(500), sentTeams(false), currteam(0)
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
    /*
    World::currteam = 0;
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
    */
    delete world;
    world = new World();
}
