#include <iostream>
#include "Windows.h"

int main(int argc, char** argv) {
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	std::cout << "������� ���: ";
	std::string name;
	std::cin >> name;
	std::cout << "������������, " << name << "!" << std::endl;
	return 0;
}