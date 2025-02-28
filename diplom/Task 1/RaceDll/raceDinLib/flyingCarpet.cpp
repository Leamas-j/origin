#include "FlyingCarpet.h"

FlyingCarpet::FlyingCarpet(float distance){
	name = "Ковер-самолет";
	this->distance = distance;
	speed = 10;
}

float FlyingCarpet::calcDecrease()
{
	int tmp{0};

	if((distance >= 1000)&&(distance < 5000)) {
		tmp = 3;
	} 
	else if((distance >= 5000) && (distance < 10000)) {
		tmp = 10;
	}
	else if (distance >= 10000) {
		tmp = 5;
	}
	return 1 - static_cast<float>(tmp) / 100;
}
