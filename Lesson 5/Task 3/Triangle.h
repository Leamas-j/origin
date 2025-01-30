#pragma once

#include "Figure.h"

class Triangle : public Figure {
public:
	Triangle(int a, int b, int c, int A, int B, int C);
	virtual std::string sides_coners_str() override;
	void print() override;
};