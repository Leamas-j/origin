#include "FlyingCarpet.h"

FlyingCarpet::FlyingCarpet(float distance){
	name = "Ковер-самолет";
	this->distance = distance;
	speed = 10;
}

float FlyingCarpet::calcDecrease()
{
	int tmp{0};
	int smallDistance{ 1000 };
	int middleDistance{ 5000 };
	int largeDistance{ 10000 };

	if((distance >= smallDistance)&&(distance < middleDistance)) {
		tmp = 3;
	} 
	else if((distance >= middleDistance) && (distance < largeDistance)) {
		tmp = 10;
	}
	else if (distance >= largeDistance) {
		tmp = 5;
	}
	return 1 - static_cast<float>(tmp) / 100;
}
