#include "RightTriangle.h"

RightTriangle::RightTriangle(int a, int b, int c, int A, int B, int C) : Triangle(a, b, c, A, B, C) {
	name = "Прямоугольный треугольник";
	this->a = a;
	this->b = b;
	this->c = c;
	this->A = A;
	this->B = B;
	this->C = C;
}
void RightTriangle::print(){
	std::cout << name << ":\n";
	if (C == 90) {
		std::cout << sides_coners_str();
	}
	else std::cout << "Неверные параметры!\n\n";
}