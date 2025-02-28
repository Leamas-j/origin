#pragma once
#include "air.h"

class EXP FlyingCarpet : public Air
{
public:
	FlyingCarpet(float distance);
	virtual float calcDecrease() override;
};

