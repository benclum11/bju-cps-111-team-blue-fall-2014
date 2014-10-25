#ifndef LOAD_H
#define LOAD_H

#include <string>
#include <iostream>

using namespace std;

class Load {

    Load(string filename);

public:

    void loadFile(ifstream &infile);

    void createTower(stringstream &sstrm);

    void createUnit(stringstream &sstrm);

    void createBase(stringstream &sstrm);
};

#endif // LOAD_H
