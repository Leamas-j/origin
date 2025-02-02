
#include "RightTriangle.h"

RightTriangle::RightTriangle(int a, int b, int c, int A, int B, int C) : Triangle(3, a, b, c, A, B, C) {
	if(C != 90) throw MyException("Ошибка создания фигуры. Причина: угол C не равен 90.");
	name = "Прямоугольный треугольник";
	this->a = a;
	this->b = b;
	this->c = c;
	this->A = A;
	this->B = B;
	this->C = C;
}
void RightTriangle::print(){
	std::cout << name << " (";
	std::cout << sides_coners_str();
}