#ifndef BUILDABLELABEL_H
#define BUILDABLELABEL_H

#include <QLabel>
#include <QWidget>
#include <QMouseEvent>

class BuildableLabel : public QLabel {

    bool clicked;
    QWidget* parent;

public:
    BuildableLabel(QWidget* parent) : QLabel(parent), parent(parent)
    {
        setMouseTracking(true);
        clicked = false;
    }

    void mouseReleaseEvent(QMouseEvent *ev);

    void setClicked(bool init) { clicked = init; }

    bool getClicked() { return clicked; }

    int getXCoord() { return this->getXCoord(); }
    int getYCoord() { return this->getYCoord(); }

};

#endif // BUILDABLELABEL_H
