#ifndef BUILDABLELABEL_H
#define BUILDABLELABEL_H

#include <QLabel>
#include <QWidget>
#include <QMouseEvent>

//#include "gamewindow.h"

class BuildableLabel : public QLabel {

    int team;
    static int clientTeam;
    bool clicked;
    QWidget* parent;

public:

    BuildableLabel(QWidget* parent, int team) : QLabel(parent), team(team), parent(parent)
    {
        setMouseTracking(true);
        clicked = false;
    }

    static void setClientTeam(int init) { BuildableLabel::clientTeam = init; }
    void mouseReleaseEvent(QMouseEvent *ev);

    QWidget* getParent() { return parent; }

    void setClicked(bool init) { clicked = init; }

    bool getClicked() { return clicked; }
    int getTeam() {return team; }
    static int getClientTeam() { return clientTeam; }

    int getXCenter() { return this->pos().x() + 25; }
    int getYCenter() { return this->pos().y() + 25; }

};

#endif // BUILDABLELABEL_H
