#pragma once

#include "Quadrangle.h"

class Square : public Quadrangle {
public:
	Square(int a, int b, int c, int d, int A, int B, int C, int D);
	void print() override;
};