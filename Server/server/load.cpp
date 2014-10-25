#include "load.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;
Load::Load(string filename) {
    ifstream infile;
    infile.open(filename);
    loadFile(infile);
    infile.close();
}

void Load::createTower(stringstream &sstrm) {
    //initialze new tower with proper instance variables
}

void Load::createUnit(stringstream &sstrm) {
    //initialze new unit with proper instance variables
}

void Load::createBase(stringstream &sstrm) {
    //initialze new base with proper instance variables
}

void Load::loadFile(ifstream &infile) {
    //write type and x y coordinates, health, of every tower, unit, and base to new file
    while (infile) {
        string line;
        getline(infile, line);
        stringstream sstrm(line);

        //string currentString;
        //sstrm >> currentString;

        if (line.find("tower") == 0) {
            createTower(sstrm);
        } else if (line.find("unit") == 0) {
            createUnit(sstrm);
        } else if (line.find("base") == 0) {
            createBase(sstrm);
        }
    }
}


