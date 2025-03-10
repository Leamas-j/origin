#pragma once
#include <iostream>

class Transport
{
public:
    Transport();
    virtual void calcRaceResult();
    virtual float calcDecrease();
    std::string getName();
    float getResult();
protected:
    std::string name;
    int speed;
    int drivingTime;
    int countRestTime;
    float* restTime;
    float result;
    float distance;
};

