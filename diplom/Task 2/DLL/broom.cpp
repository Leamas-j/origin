#include "broom.h"

Broom::Broom(float distance)
{
	name = "Метла";
	this->distance = distance;
	speed = 20;
}

float Broom::calcDecrease()
{	
	return 1 - static_cast<float>(static_cast<int>(distance / 1000) / 100.0f);;
}
