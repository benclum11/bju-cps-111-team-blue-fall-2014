#include "units.h"

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

        //Chooses image set for the unit
        if (type == 1) //basic
        {
            picture = "://Resources/Units/0/";
        } else if (type == 2) //fast
        {
            picture = "://Resources/Units/1/";
        } else if (type == 3) //heavy
        {
            picture = "://Resources/Units/2/";
        }

        //Adds remaining text of an actual image
        if (facing == 1) //north
        {
            picture = picture + "1.png";
        } else if (facing == 2) //east
        {
            picture = picture + "2.png";
        } else if (facing == 3) //south
        {
            picture = picture + "3.png";
        } else if (facing == 4)//west
        {
            picture = picture + "4.png";
        }

        image = new QLabel(display);
        image->setPixmap(QPixmap(picture));
        image->setGeometry(x,y,15,15);
        image->setScaledContents(true);
        image->show();
    }
}

void units::setXY(int xCoord, int yCoord)
{
    x = xCoord;
    y = yCoord;
}

void units::setFacing(int direction)
{
    facing = direction;
}

void units::setCurHealth(int health)
{
    curHealth = health;
}

void units::killUnit()
{

}


