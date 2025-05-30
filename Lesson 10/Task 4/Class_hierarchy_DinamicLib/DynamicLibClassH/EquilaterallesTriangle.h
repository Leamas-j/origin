#pragma once

#include "Triangle.h"

#ifdef DYNAMICLIBCLASSH_EXPORTS
#define EXP __declspec(dllexport)
#else
#define EXP __declspec(dllimport)
#endif

class EXP EquilaterallesTriangle : public Triangle {
public:
	EquilaterallesTriangle(int a, int b, int c, int A, int B, int C);
	void print() override;
};