#include "ground.h"
#include "myException.h"

void Ground::calcRaceResult(){
    if(!speed || !drivingTime) throw MyException("Division by zero");
    float result = distance / speed;
    int restCount = static_cast<int>(result/drivingTime);
    if ((static_cast<int>(result) % drivingTime) == 0) {
        --restCount;
    }
    for(int i = 0; i < restCount; ++i){
        if(i < countRestTime){
            result += restTime[i];
        }
        else{
            result += restTime[countRestTime-1];
        }
    }    
    this->result = result;
}

