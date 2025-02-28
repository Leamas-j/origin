#pragma once
#include "air.h"
class Eagle :  public Air
{
public:
	Eagle(float distance);
	virtual float calcDecrease() override;
};

