
#include <iostream>
#include "RightTriangle.h"
#include "IsoscelesTriangle.h"
#include "EquilaterallesTriangle.h"
#include "Rectangle.h"
#include "Square.h"
#include "Parallelogram.h"
#include "Rhomb.h"

void print_info(Figure* figure) {
	figure->print();
}


int main()
{
	setlocale(LC_ALL, "RU");

	Triangle tr(10, 20, 30, 50, 60, 70);
	print_info(&tr);

	RightTriangle rtr(10, 20, 30, 50, 60, 90);
	print_info(&rtr);

	IsoscelesTriangle itr(10, 20, 10, 50, 60, 50);
	print_info(&itr);

	EquilaterallesTriangle etr(30, 30, 30, 60, 60, 60);
	print_info(&etr);

	Quadrangle qu(10, 20, 30, 40, 50, 60, 70, 80);
	print_info(&qu);

	Rectangle re(10, 20, 10, 20, 90, 90, 90, 90);
	print_info(&re);

	Square sq(20, 20, 20, 20, 90, 90, 90, 90);
	print_info(&sq);

	Parallelogram pa(20, 30, 20, 30, 30, 40, 30, 40);
	print_info(&pa);

	Rhomb rh(30, 30, 30, 30, 30, 40, 30, 40);
	print_info(&rh);
}

