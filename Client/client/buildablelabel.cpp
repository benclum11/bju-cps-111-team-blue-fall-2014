#include "buildablelabel.h"


void BuildableLabel::mouseReleaseEvent(QMouseEvent *ev)
{
    (void)ev;
    for (QObject* obj: parent->children()) {
        BuildableLabel* lbl = dynamic_cast<BuildableLabel*>(obj);
        lbl->setClicked(false);
    }
    clicked = true;
}
