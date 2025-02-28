#pragma once
#include <iostream>

#ifdef RACEDINLIB_EXPORTS
#define EXP __declspec(dllexport)
#else
#define EXP __declspec(dllimport)
#endif

class EXP Transport
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

