#include "EquilaterallesTriangle.h"
#include "MyException.h"

EquilaterallesTriangle::EquilaterallesTriangle(int a, int b, int c, int A, int B, int C) : Triangle(3, a, b, c, A, B, C){
	if((a != c) || (a != b) || (b != c)) throw MyException("Ошибка создания фигуры. Причина: стороны не равны.");
	if((A != 60) || (B != 60) || (C != 60)) throw MyException("Ошибка создания фигуры. Причина: углы не 60 градусов.");
	name = "Равносторонний треугольник";
	this->a = a;
	this->b = b;
	this->c = c;
	this->A = A;
	this->B = B;
	this->C = C;
}

void EquilaterallesTriangle::print(){
	std::cout << name << " (";
	std::cout << sides_coners_str();
}