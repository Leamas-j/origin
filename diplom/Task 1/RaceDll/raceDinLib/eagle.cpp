#include "eagle.h"

Eagle::Eagle(float distance){
	name = "����";
	this->distance = distance;
	speed = 8;
}

float Eagle::calcDecrease()
{
	return 0.94f;
}
