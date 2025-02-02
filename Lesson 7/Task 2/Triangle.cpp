#include "Triangle.h"

Triangle::Triangle(int sides_count, int a, int b, int c, int A, int B, int C) {
	if(sides_count != 3) throw MyException("������ �������� ������. �������: ������ �� 3.");
	if((A+B+C) != 180) throw MyException("������ �������� ������. �������: ����� ����� �� ����� 180.");
	this->name = "�����������";	
	this->sides_count = 3;		
	this->a = a;
	this->b = b;
	this->c = c;
	this->A = A;
	this->B = B;
	this->C = C;
}

std::string Triangle::sides_coners_str(){
	std::string tmpString =
		"������� " + std::to_string(a) + ", " + std::to_string(b) + ", " + std::to_string(c) + "; " +
		"���� " + std::to_string(A) + ", " + std::to_string(B) + ", " + std::to_string(C) + ") ������\n\n";
	return tmpString;
}

void Triangle::print(){
	std::cout << name << " (" << sides_coners_str();
}