#include "choosetower.h"

void ChooseTower::mouseReleaseEvent(QMouseEvent *ev) {
    (void)ev;
    for (QObject* obj: parent->children()) {
        ChooseTower* lbl = dynamic_cast<ChooseTower*>(obj);
        if (lbl != NULL) {
            lbl->setClicked(false);
        }
    }
    clicked = true;
}
