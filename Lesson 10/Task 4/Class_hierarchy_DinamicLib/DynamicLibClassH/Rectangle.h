#pragma once

#include "Quadrangle.h"

#ifdef DYNAMICLIBCLASSH_EXPORTS
#define EXP __declspec(dllexport)
#else
#define EXP __declspec(dllimport)
#endif 

class EXP Rectangle : public Quadrangle {
public:
	Rectangle(int a, int b, int c, int d, int A, int B, int C, int D);
	void print() override;
};