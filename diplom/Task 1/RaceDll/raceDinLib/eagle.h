#pragma once
#include "air.h"

class EXP Eagle :  public Air
{
public:
	Eagle(float distance);
	virtual float calcDecrease() override;
};

