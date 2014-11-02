#ifndef BUILDABLELABEL_H
#define BUILDABLELABEL_H

#include <QLabel>
#include <QWidget>
#include <QMouseEvent>

#include "gamewindow.h"

class BuildableLabel : public QLabel {

    static int clientTeam;
    int team;
    bool clicked;
    QWidget* parent;

public:
    BuildableLabel(QWidget* parent, int team) : QLabel(parent), team(team), parent(parent)
    {
        setMouseTracking(true);
        clicked = false;
    }

    static void setClientTeam(int init) {BuildableLabel::clientTeam = init;}

    void mouseReleaseEvent(QMouseEvent *ev);

    void setClicked(bool init) { clicked = init; }

    bool getClicked() { return clicked; }

    int getXCoord() { return this->getXCoord(); }
    int getYCoord() { return this->getYCoord(); }

};

#endif // BUILDABLELABEL_H
