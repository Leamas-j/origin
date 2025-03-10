#include "camel.h"

Camel::Camel(float distance)
{
    name = "Верблюд";    
    speed = 10;
    drivingTime = 30;
    countRestTime = 2;
    restTime = new float[countRestTime]{5, 8};
    this->distance = distance;
}
Camel::~Camel() {
    delete[] restTime;
}

