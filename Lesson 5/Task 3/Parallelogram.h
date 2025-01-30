#pragma once

#include "Quadrangle.h"

class Parallelogram : public Quadrangle {
public:
	Parallelogram(int a, int b, int c, int d, int A, int B, int C, int D);
	void print() override;
};