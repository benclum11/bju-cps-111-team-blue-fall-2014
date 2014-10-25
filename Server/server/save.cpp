#include "save.h"
#include <string>
#include <fstream>
#include <iostream>

using namespace std;


Save::Save(string filename) {
    ifstream infile;
    infile.open(filename);
    saveFile(infile);
    infile.close();
}

void Save::saveFile(ifstream &infile) {
    //read type and x y coordinates, health, of every tower, unit, and base
    //intialize all instance variables
}

