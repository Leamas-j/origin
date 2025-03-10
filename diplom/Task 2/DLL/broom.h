#pragma once

#include "air.h"

class Broom :  public Air
{
public:
	Broom(float distance);
	virtual float calcDecrease() override;
};

