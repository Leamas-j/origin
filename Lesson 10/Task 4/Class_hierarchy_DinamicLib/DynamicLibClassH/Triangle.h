#pragma once

#include "Figure.h"

#ifdef DYNAMICLIBCLASSH_EXPORTS
#define EXP __declspec(dllexport)
#else
#define EXP __declspec(dllimport)
#endif

class EXP Triangle : public Figure {
public:
	Triangle(int a, int b, int c, int A, int B, int C);
	virtual std::string sides_coners_str() override;
	void print() override;
};