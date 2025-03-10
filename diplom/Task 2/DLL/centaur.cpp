#include "centaur.h"
Centaur::Centaur(float distance)
{
    name = "Кентавр";   
    speed = 15;
    drivingTime = 8;
    countRestTime = 1;
    restTime = new float[countRestTime]{2}; 
    this->distance = distance;
}

Centaur::~Centaur(){
    delete [] restTime;
}
