#include "roverboots.h"

RoverBoots::RoverBoots(float distance)
{
    name = "Ботинки-вездеходы";
    speed = 6;
    drivingTime = 60;
    countRestTime = 2;
    restTime = new float[countRestTime]{10, 5};
    this->distance = distance;
}
RoverBoots::~RoverBoots(){
    delete [] restTime;
}
