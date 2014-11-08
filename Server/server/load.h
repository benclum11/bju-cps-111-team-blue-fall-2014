#ifndef LOAD_H
#define LOAD_H

#include <QString>
#include <QStringList>
#include <QFile>
#include "world.h"

using namespace std;

class Load {

public:

    Load(QString filename);

private:

    void loadFile(QFile &file);
};

#endif // LOAD_H
