#pragma once
#include "air.h"

class FlyingCarpet : public Air
{
public:
	FlyingCarpet(float distance);
	float calcDecrease() override;
};

