#include "choosetower.h"
#include "highlightedlabel.h"

void ChooseTower::mouseReleaseEvent(QMouseEvent *ev) {
    (void)ev;
    for (QObject* obj: parent->children()) {
        ChooseTower* lbl = dynamic_cast<ChooseTower*>(obj);
        if (lbl != NULL || lbl != nullptr) {
            lbl->setClicked(false);
        }
        HighlightedLabel *label = dynamic_cast<HighlightedLabel*>(obj);
        if (label != NULL) {
            label->setPixmap(QPixmap(":/Resources/frameythingy.png"));
            label->setScaledContents(true);
            label->setGeometry(this->geometry());
            label->show();
            label->raise();
            label->raise();
        }
    }
    clicked = true;
}

void ChooseTower::make(QString resource, int x, int y, int w, int h, bool scaled)
{
    this->setPixmap(QPixmap(resource));
    this->setGeometry(x, y, w, h);
    this->setScaledContents(scaled);
    this->raise();
    this->show();
}
