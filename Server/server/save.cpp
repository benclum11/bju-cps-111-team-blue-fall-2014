#include "save.h"
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

Save::Save(string filename) {
    ifstream infile;
    infile.open(filename);
    //create file to save
    infile.close();
}

void Save::saveFile() {
    //write type and x y coordinates, health, of every tower, unit, and base to new file
    //intialize all instance variables
}
