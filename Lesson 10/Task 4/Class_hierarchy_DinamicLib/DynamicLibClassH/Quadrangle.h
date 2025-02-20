#pragma once

#include "Figure.h"

#ifdef DYNAMICLIBCLASSH_EXPORTS
#define EXP __declspec(dllexport)
#else
#define EXP __declspec(dllimport)
#endif

class EXP Quadrangle : public Figure {
public:
	Quadrangle(int a, int b, int c, int d, int A, int B, int C, int D);
	virtual std::string sides_coners_str() override;
	void print() override;
};