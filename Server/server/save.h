#ifndef SAVE_H
#define SAVE_H

#include <QString>
#include <QFile>
#include <QCoreApplication>
#include <QTextStream>

using namespace std;

class Save {

public:
    Save(QString filename);

private:
    void saveFile(QFile &file);
};

#endif // SAVE_H
