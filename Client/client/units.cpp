#include "units.h"

units::units(QString unitType, int loyalty, int health, int xCoord, int yCoord, int direction)
{
    type = unitType; //this does not currently match the documentation and should fail
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
