#pragma once

#include "air.h"

class EXP Broom :  public Air
{
public:
	Broom(float distance);
	float calcDecrease() override;
};

