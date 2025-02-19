#include <iostream>
#include "Windows.h"

#include "Leaver.h"

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	std::cout << "¬ведите им€: ";
	std::string name;
	std::cin >> name;
	Leaver l(name);
	std::cout << l.leave() << std::endl;
}