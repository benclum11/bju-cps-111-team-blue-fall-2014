#ifndef CHOOSETOWER_H
#define CHOOSETOWER_H

#include <QLabel>
#include <QWidget>

class ChooseTower : public QLabel {

    bool clicked;
    QWidget* parent;
    int towerNumber;

public:
    ChooseTower(QWidget* parent, int init) : QLabel(parent), towerNumber(init), parent(parent) { clicked = false; }

    bool getClicked() { return clicked; }
    int getTowerNumber() { return towerNumber; }

    void setClicked(bool init) { clicked = init; }

    void mouseReleaseEvent(QMouseEvent *ev);
};


#endif // CHOOSETOWER_H
