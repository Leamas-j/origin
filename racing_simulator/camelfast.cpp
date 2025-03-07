#include "camelfast.h"

CamelFast::CamelFast(float distance)
{
    name = "Верблюд-быстроход";    
    speed = 40;
    drivingTime = 10;
    countRestTime = 3;
    restTime = new float[countRestTime]{5, 6.5, 8};
    this->distance = distance;
}
CamelFast::~CamelFast(){
    delete[] restTime;
}
