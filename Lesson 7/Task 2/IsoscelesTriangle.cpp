#include "IsoscelesTriangle.h"

IsoscelesTriangle::IsoscelesTriangle(int a, int b, int c, int A, int B, int C) : Triangle(3, a, b, c, A, B, C){
	if(a != c ) throw MyException("Ошибка создания фигуры. Причина: стороны при основании не равны.");
	if(A != C) throw MyException("Ошибка создания фигуры. Причина: углы при основании не равны.");
	name = "Равнобедренный треугольник";
	this->a = a;
	this->b = b;
	this->c = c;
	this->A = A;
	this->B = B;
	this->C = C;
}

void IsoscelesTriangle::print(){
	std::cout << name << " (";
	std::cout << sides_coners_str();
}

