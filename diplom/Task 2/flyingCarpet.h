#pragma once
#include "air.h"
class FlyingCarpet : public Air
{
public:
	FlyingCarpet(float distance);
	virtual float calcDecrease() override;
};

