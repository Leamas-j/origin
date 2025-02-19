#include "IsoscelesTriangle.h"

IsoscelesTriangle::IsoscelesTriangle(int a, int b, int c, int A, int B, int C) : Triangle(a, b, c, A, B, C){
	name = "Равнобедренный треугольник";
	this->a = a;
	this->b = b;
	this->c = c;
	this->A = A;
	this->B = B;
	this->C = C;
}

void IsoscelesTriangle::print(){
	std::cout << name << ":\n";
	if ((a == c) && (A == C)) {
		std::cout << sides_coners_str();
	}
	else std::cout << "Неверные параметры!\n\n";
}

