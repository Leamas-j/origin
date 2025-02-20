#pragma once

#include <iostream>
#include <string>

#ifdef DYNAMICLIBCLASSH_EXPORTS
#define EXP __declspec(dllexport)
#else
#define EXP __declspec(dllimport)
#endif

class EXP Figure {
protected:
	int sides_count;
	std::string name;
	int a, b, c, d;
	int A, B, C, D;
public:
	Figure();
	virtual void print() = 0;
	virtual std::string sides_coners_str() = 0;
};