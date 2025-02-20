#pragma once

#include "Quadrangle.h"

#ifdef DYNAMICLIBCLASSH_EXPORTS
#define EXP __declspec(dllexport)
#else
#define EXP __declspec(dllimport)
#endif 

class EXP Rhomb : public Quadrangle {
public:
	Rhomb(int a, int b, int c, int d, int A, int B, int C, int D);
	void print() override;
};