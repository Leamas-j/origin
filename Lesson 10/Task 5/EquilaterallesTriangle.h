#pragma once

#include "Triangle.h"

class EquilaterallesTriangle : public Triangle {
public:
	EquilaterallesTriangle(int a, int b, int c, int A, int B, int C);
	void print() override;
};