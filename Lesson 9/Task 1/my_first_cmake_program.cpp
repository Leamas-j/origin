#include <iostream>
#include "Windows.h"

int main(int argc, char** argv) {
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	std::cout << "Введите имя: ";
	std::string name;
	std::cin >> name;
	std::cout << "Здравствуйте, " << name << "!" << std::endl;
	return 0;
}