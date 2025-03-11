#pragma once
#include "air.h"

class Eagle :  public Air
{
public:
	Eagle(float distance);
	float calcDecrease() override;
};

