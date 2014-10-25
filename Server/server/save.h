#ifndef SAVE_H
#define SAVE_H

#include <string>
#include <iostream>

using namespace std;

class Save {

    Save(string filename);

    void saveFile(ifstream &infile);
};

#endif // SAVE_H
