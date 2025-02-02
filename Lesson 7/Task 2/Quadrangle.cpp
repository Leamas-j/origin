
#include "Quadrangle.h"

Quadrangle::Quadrangle(int sides_count, int a, int b, int c, int d, int A, int B, int C, int D) {
	if(sides_count != 4) throw MyException("������ �������� ������. �������: ������ �� 4.");
	if ((A + B + C + D) != 360) throw MyException("������ �������� ������. �������: ����� ����� �� ����� 360.");
	name = "��������������";
	this->sides_count = sides_count;	
	this->a = a;
	this->b = b;
	this->c = c;
	this->d = d;
	this->A = A;
	this->B = B;
	this->C = C;
	this->D = D;
}

std::string Quadrangle::sides_coners_str(){
	std::string tmpString =
		"������� " + std::to_string(a) + ", " + std::to_string(b) + ", " + std::to_string(c) + ", " + std::to_string(d) + "; " +
		"���� " + std::to_string(A) + ", " + std::to_string(B) + ", " + std::to_string(C) + ", " + std::to_string(D) + ") ������\n\n";
	return tmpString;
}
void Quadrangle::print(){
	std::cout << name << " (" << sides_coners_str();
}