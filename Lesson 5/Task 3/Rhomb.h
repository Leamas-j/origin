#pragma once

#include "Quadrangle.h"

class Rhomb : public Quadrangle {
public:
	Rhomb(int a, int b, int c, int d, int A, int B, int C, int D);
	void print() override;
};