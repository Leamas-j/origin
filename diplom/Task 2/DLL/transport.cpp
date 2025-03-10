#include "transport.h"

Transport::Transport(): name{}, speed{}, drivingTime{}, countRestTime{}, restTime{}, result{}, distance{}
{    
}

std::string Transport::getName(){
    return name;
}

float Transport::getResult(){
    return result;
}

void Transport::calcRaceResult(){
    result = 0;
}

float Transport::calcDecrease() {
    return 0;
}






