#pragma once

#include "Quadrangle.h"

#ifdef DYNAMICLIBCLASSH_EXPORTS
#define EXP __declspec(dllexport)
#else
#define EXP __declspec(dllimport)
#endif

class EXP Square : public Quadrangle {
public:
	Square(int a, int b, int c, int d, int A, int B, int C, int D);
	void print() override;
};