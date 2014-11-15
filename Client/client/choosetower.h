#ifndef CHOOSETOWER_H
#define CHOOSETOWER_H

#include <QLabel>
#include <QWidget>

class ChooseTower : public QLabel {

    bool clicked;
    QWidget* parent;
    int towerNumber;

public:
    ChooseTower(QWidget* parent, int init) : QLabel(parent), parent(parent), towerNumber(init) { clicked = false; }

    bool getClicked() { return clicked; }
    int getTowerNumber() { return towerNumber; }

    void setClicked(bool init) { clicked = init; }

    void mouseReleaseEvent(QMouseEvent *ev);

    void make(QString resource,  int x, int y, int w, int h, bool scaled);
};


#endif // CHOOSETOWER_H
