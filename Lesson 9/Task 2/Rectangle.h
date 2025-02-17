#pragma once

#include "Quadrangle.h"

class Rectangle : public Quadrangle {
public:
	Rectangle(int a, int b, int c, int d, int A, int B, int C, int D);
	void print() override;
};