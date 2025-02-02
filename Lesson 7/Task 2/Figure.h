#pragma once

#include "MyException.h"
#include <iostream>
#include <string>

class Figure {
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