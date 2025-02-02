
#include "Rhomb.h"

Rhomb::Rhomb(int a, int b, int c, int d, int A, int B, int C, int D) : Quadrangle(4, a, b, c, d, A, B, C, D){
	if((a != c) || (a != b) || (a != d) || (b != c) || (b != d) || (d != c)) throw MyException("Ошибка создания фигуры. Причина: стороны не равны.");
	if((A != C) || (B != D)) throw MyException("Ошибка создания фигуры. Причина: противоположные углы не равны.");
	name = "Ромб";
	this->a = a;
	this->b = b;
	this->c = c;
	this->d = d;
	this->A = A;
	this->B = B;
	this->C = C;
	this->D = D;
}
void Rhomb::print(){
	std::cout << name + " (";
	std::cout << sides_coners_str();
}