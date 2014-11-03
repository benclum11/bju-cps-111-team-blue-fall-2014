#include "units.h"

units::units(unitType, loyalty, health, xCoord, yCoord, direction)
{
    type = unitType; //this needs more processing to work. See documentation
    team = loyalty;
    curHealth = maxHealth = health;
    x = xCoord;
    y = yCoord;
    facing = direction;
    std::string picture;

    //Chooses image set for the unit
    if (type == "1") //basic
    {
        picture = "://Resources/Units/0/";
    } else if (type == "2") //fast
    {
        picture = "://Resources/Units/1/";
    } else //heavy
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
    } else //west
    {
        picture = picture + "4.png";
    }

    image = new QLabel(actionDisplay);
    image->setPixmap(QPixmap(picture));
    image->setGeometry(x,y,15,15);
    image->setScaledContents(true);
    image->show();
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
