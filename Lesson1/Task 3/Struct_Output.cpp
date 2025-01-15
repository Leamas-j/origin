// Struct_Output.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "Windows.h"

struct Address {
	std::string city;
	std::string street;
	int house;
	int flat;
	int postCode;
};

void displayAddress(const Address& adr);

int main()
{
	SetConsoleOutputCP(1251);

	Address a1 = { "Москва", "Арбат", 12, 8, 123456 };
	Address a2 = { "Ижевск", "Пушкина", 59, 143, 953769 };

	displayAddress(a1);
	displayAddress(a2);
	
	return 0;
}

void displayAddress(const Address& adr) {
	std::cout << "Город: " << adr.city << std::endl;
	std::cout << "Улица: " << adr.street << std::endl;
	std::cout << "Номер дома: " << adr.house << std::endl;
	std::cout << "Номер квартиры: " << adr.flat << std::endl;
	std::cout << "Индекс: " << adr.postCode << std::endl << std::endl;
}
