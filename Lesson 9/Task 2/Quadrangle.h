#pragma once

#include "Figure.h"

class Quadrangle : public Figure {
public:
	Quadrangle(int a, int b, int c, int d, int A, int B, int C, int D);
	virtual std::string sides_coners_str() override;
	void print() override;
};