#include "world.h"
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

// Global static pointer used to ensure a single instance of the class.
World* World::world = NULL;

World* World::Instance() {
    if(!world) {
        world = new World();
    }
    return world;
}

World::World() {

    readMapFile();

}

void World::readMapFile() {

    ifstream readmap;
    readmap.open("://textfiles/map.txt");
    char temp[10];
    readmap.getline(temp,4);
    int rows = stoi(temp);
    readmap.getline(temp,4);
    int columns = stoi(temp);

    map = new Tile**[rows];
    for (int i = 0; i < rows; ++i) {
        map[i] = new Tile*[columns];
        for (int j = 0; j < columns; ++j) {
            map[i][j] = new Tile();
        }
    }
}
