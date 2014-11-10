//This files contains code to create, display, and move the units.

#include "units.h"
#include <QProgressBar>

// Creates a QString containing the needed resource address
QString createImageString(int unitType, int direction)
{
    QString picture = "";

    //Chooses image set for the unit
    if (unitType == 0) //basic
    {
        picture = "://Resources/Units/0/";
    } else if (unitType == 1) //fast
    {
        picture = "://Resources/Units/1/";
    } else if (unitType == 2) //heavy
    {
        picture = "://Resources/Units/2/";
    }

    //Adds remaining text of an actual image
    if (direction == 1) //north
    {
        picture = picture + "1.png";
    } else if (direction == 2) //east
    {
        picture = picture + "2.png";
    } else if (direction == 3) //south
    {
        picture = picture + "3.png";
    } else if (direction == 4)//west
    {
        picture = picture + "4.png";
    }

    return picture;
}

// Breaks unit type QString into relevant parts which are saved in the unit's instance variables.
bool units::processType(QString unitType, units *instance)
{
    QStringList typeArgs = unitType.split("_");

    bool ok;
    int firstVal = typeArgs.at(0).toInt(&ok, 10);
    if (ok) instance->type = typeArgs.at(1).toInt(&ok, 10);
    if (ok) instance->level = typeArgs.at(2).toInt(&ok, 10);

    if (ok && firstVal == 2)
    {
        return true;
    } else
    {
        return false;
    }
}

// Note that this constructor does nothing with the level variable. I don't think it needs to either.
units::units(QString unitType,int xCoord, int yCoord, int direction, QWidget *display)
{
    if (processType(unitType, this))
    {
        x = xCoord-25;
        y = yCoord-25;
        facing = direction;
        QString picture;
        int type = unitType.split("_").at(1).toInt();

        picture = createImageString(type, facing);

        //image = new QLabel(display);
        this->setParent(display);
        this->setPixmap(QPixmap(picture));
        this->setGeometry(x,y,50,50);
        this->setScaledContents(true);
        this->raise();
        this->raise();
        this->show();

        QProgressBar* healthbar = new QProgressBar(this);
        healthbar->setGeometry(10,0,30,10);
        healthbar->setValue(100);
        healthbar->setTextVisible(false);
        healthbar->show();
    }
}

void units::setXY(int xCoord, int yCoord)
{
    x = xCoord-25;
    y = yCoord-25;
}

void units::setFacing(int direction)
{
    QString picture = createImageString(type, direction);
    this->setPixmap(QPixmap(picture));
    // Do I need to do more? this->show(); perhaps?
}

void units::setCurHealth(int health)
{
    for(QObject* obj : this->children()) {
        QProgressBar* bar = dynamic_cast<QProgressBar*>(obj);
        if(bar != nullptr) {
            bar->setValue(health);
        }
    }
}

void units::killUnit()
{

}


