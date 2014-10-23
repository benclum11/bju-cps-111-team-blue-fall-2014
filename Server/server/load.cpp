#include "load.h"
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

Load::Load(string filename) {
    ifstream infile;
    infile.open(filename);
    //create file to load
    infile.close();
}

void Load::loadFile() {

}


