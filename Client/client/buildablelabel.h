#ifndef BUILDABLELABEL_H
#define BUILDABLELABEL_H

#include <QLabel>
#include <QWidget>

class BuildableLabel : public QLabel {

public:
    BuildableLabel(QWidget* parent) : QLabel(parent) {}

};

#endif // BUILDABLELABEL_H
