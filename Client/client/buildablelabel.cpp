#include "buildablelabel.h"
#include "highlightedlabel.h"

void BuildableLabel::mouseReleaseEvent(QMouseEvent *ev)
{
    (void)ev;
    for (QObject* obj: parent->children()) {
        BuildableLabel* lbl = dynamic_cast<BuildableLabel*>(obj);
        if (lbl != NULL) {
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
