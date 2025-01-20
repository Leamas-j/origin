// Months.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "Windows.h"

enum months {
	January = 1,
	February,
	March,
	April,
	May,
	June,
	July,
	August,
	September,
	October,
	November,
	December
};

int main()
{
	SetConsoleOutputCP(1251);
	int monthNum;
	do {
		std::cout << "Введите номер месяца: ";
		std::cin >> monthNum;
		switch (monthNum) {
		case 0:
			std::cout << "До свидания" << std::endl;
			break;
		case static_cast<int>(January):
			std::cout << "Январь" << std::endl;
			break;
		case static_cast<int>(February):
			std::cout << "Февраль" << std::endl;
			break;
		case static_cast<int>(March):
			std::cout << "Март" << std::endl;
			break;
		case static_cast<int>(April):
			std::cout << "Апрель" << std::endl;
			break;
		case static_cast<int>(May):
			std::cout << "Май" << std::endl;
			break;
		case static_cast<int>(June):
			std::cout << "Июнь" << std::endl;
			break;
		case static_cast<int>(July):
			std::cout << "Июль" << std::endl;
			break;
		case static_cast<int>(August):
			std::cout << "Август" << std::endl;
			break;
		case static_cast<int>(September):
			std::cout << "Сентябрь" << std::endl;
			break;
		case static_cast<int>(October):
			std::cout << "Октябрь" << std::endl;
			break;
		case static_cast<int>(November):
			std::cout << "Ноябрь" << std::endl;
			break;
		case static_cast<int>(December):
			std::cout << "Декабрь" << std::endl;
			break;
		default:
			std::cout << "Неправильный номер!" << std::endl;
		}
	} while (monthNum != 0);
	return 0;
}

