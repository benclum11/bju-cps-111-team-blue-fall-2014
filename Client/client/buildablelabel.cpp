#include "buildablelabel.h"


void BuildableLabel::mouseReleaseEvent(QMouseEvent *ev)
{
    (void)ev;
    for (QObject* obj: parent->children()) {
        BuildableLabel* lbl = dynamic_cast<BuildableLabel*>(obj);
        if (lbl != NULL) {
            lbl->setClicked(false);
        }
    }
    clicked = true;
}
