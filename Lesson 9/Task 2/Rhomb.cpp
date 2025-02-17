#include "Rhomb.h"

Rhomb::Rhomb(int a, int b, int c, int d, int A, int B, int C, int D) : Quadrangle(a, b, c, d, A, B, C, D){
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
	std::cout << name + ":\n";
	if ((a == c) && (a == b) && (a == d) && (A == C) && (B == D)) {
		std::cout << sides_coners_str();
	}
	else std::cout << "Неверные параметры!\n\n";
}