#include "Triangle.h"

Triangle::Triangle(int a, int b, int c, int A, int B, int C) {
	sides_count = 3;
	name = "�����������";
	this->a = a;
	this->b = b;
	this->c = c;
	this->A = A;
	this->B = B;
	this->C = C;
}

std::string Triangle::sides_coners_str(){
	std::string tmpString =
		"�������: a=" + std::to_string(a) + " b=" + std::to_string(b) + " c=" + std::to_string(c) + "\n" +
		"����: A=" + std::to_string(A) + " B=" + std::to_string(B) + " C=" + std::to_string(C) + "\n\n";
	return tmpString;
}

void Triangle::print(){
	std::cout << name << ":\n" << sides_coners_str();
}