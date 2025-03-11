#pragma once

#include "air.h"

class Broom :  public Air
{
public:
	Broom(float distance);
	float calcDecrease() override;
};

