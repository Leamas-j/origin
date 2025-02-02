
#include "Rectangle.h"

Rectangle::Rectangle(int a, int b, int c, int d, int A, int B, int C, int D) : Quadrangle(4, a, b, c, d, A, B, C, D){
	if((a != c) || (b != d)) throw MyException("������ �������� ������. �������: ��������������� ������� �� �����.");
	if((A != 90) || (B != 90) || (C != 90) || (D != 90)) throw MyException("������ �������� ������. �������: ���� �� 90 ��������.");
	name = "�������������";
	this->a = a;
	this->b = b;
	this->c = c;
	this->d = d;
	this->A = A;
	this->B = B;
	this->C = C;
	this->D = D;
}

void Rectangle::print() {
	std::cout << name + " (";	
	std::cout << sides_coners_str();	
}