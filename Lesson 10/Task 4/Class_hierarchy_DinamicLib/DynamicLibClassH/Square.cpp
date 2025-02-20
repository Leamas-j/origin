#include "Square.h"

Square::Square(int a, int b, int c, int d, int A, int B, int C, int D) : Quadrangle(a, b, c, d, A, B, C, D) {
	name = "Квадрат";
	this->a = a;
	this->b = b;
	this->c = c;
	this->d = d;
	this->A = A;
	this->B = B;
	this->C = C;
	this->D = D;
}
void Square::print(){
	std::cout << name + ":\n";
	if ((a == c) && (a == b) && (a == d) && (A == 90) && (B == 90) && (C == 90) && (D == 90)) {
		std::cout << sides_coners_str();
	}
	else std::cout << "Неверные параметры!\n\n";
}