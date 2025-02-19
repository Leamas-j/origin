#include <iostream>
#include "Windows.h"

#include "Greeter.h"

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	std::cout << "¬ведите им€: ";
	std::string name;
	std::cin >> name;
	Greeter gr(name);
	std::cout << gr.greet() << std::endl;
}