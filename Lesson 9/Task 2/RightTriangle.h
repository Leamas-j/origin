#pragma once

#include "Triangle.h"

class RightTriangle : public Triangle {
public:
	RightTriangle(int a, int b, int c, int A, int B, int C);
	void print() override;
};