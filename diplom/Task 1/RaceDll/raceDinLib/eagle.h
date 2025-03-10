#pragma once
#include "air.h"

class EXP Eagle :  public Air
{
public:
	Eagle(float distance);
	float calcDecrease() override;
};

