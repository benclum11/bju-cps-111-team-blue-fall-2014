#include "units.h"

// Creates a QString containing the needed resource address
QString createImageString(int unitType, int direction)
{
    QString picture;

    //Chooses image set for the unit
    if (unitType == 1) //basic
    {
        picture = "://Resources/Units/0/";
    } else if (unitType == 2) //fast
    {
        picture = "://Resources/Units/1/";
    } else if (unitType == 3) //heavy
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

//Note that this constructor currently does nothing with the level variable.
units::units(QString unitType, int loyalty, int health, int xCoord, int yCoord, int direction, QWidget *display)
{
    if (processType(unitType, this))
    {
        team = loyalty;
        curHealth = maxHealth = health;
        x = xCoord;
        y = yCoord;
        facing = direction;
        QString picture;

        picture = createImageString(type, facing);

        //image = new QLabel(display);
        this->setParent(display);
        this->setPixmap(QPixmap(picture));
        this->setGeometry(x,y,15,15);
        this->setScaledContents(true);
        this->show();
    }
}

void units::setXY(int xCoord, int yCoord)
{
    x = xCoord;
    y = yCoord;
}

void units::setFacing(int direction)
{
    QString picture = createImageString(type, direction);
    this->setPixmap(QPixmap(picture));
    // Do I need to do more? this->show(); perhaps?
}

void units::setCurHealth(int health)
{
    curHealth = health;
}

void units::killUnit()
{

}


