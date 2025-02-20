#include "EquilaterallesTriangle.h"

EquilaterallesTriangle::EquilaterallesTriangle(int a, int b, int c, int A, int B, int C) : Triangle(a, b, c, A, B, C){
	name = "Равносторонний треугольник";
	this->a = a;
	this->b = b;
	this->c = c;
	this->A = A;
	this->B = B;
	this->C = C;
}

void EquilaterallesTriangle::print(){
	std::cout << name << ":\n";
	if ((a == c) && (a == b) && (A == 60) && (B == 60) && (C == 60)) {
		std::cout << sides_coners_str();
	}
	else std::cout << "Неверные параметры!\n\n";
}