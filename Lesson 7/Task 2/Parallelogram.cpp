
#include "Parallelogram.h"

Parallelogram::Parallelogram(int a, int b, int c, int d, int A, int B, int C, int D) : Quadrangle(4, a, b, c, d, A, B, C, D){
	if((a != c) || (b != d)) throw MyException("������ �������� ������. �������: ��������������� ������� �� �����.");
	if((A != C) || (B != D)) throw MyException("������ �������� ������. �������: ��������������� ���� �� �����.");
	name = "��������������";
	this->a = a;
	this->b = b;
	this->c = c;
	this->d = d;
	this->A = A;
	this->B = B;
	this->C = C;
	this->D = D;
}
void Parallelogram::print(){
	std::cout << name + " (";
	std::cout << sides_coners_str();	
}