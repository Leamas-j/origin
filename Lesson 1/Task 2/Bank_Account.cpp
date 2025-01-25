// Bank_Account.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "Windows.h"

struct bankAccount {
	unsigned int accountNum;
	std::string name;
	double money;
};

void changeMoney(bankAccount& b, const double newMoney);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	bankAccount ba;
	std::cout << "Введите номер счета: ";
	std::cin >> ba.accountNum;
	std::cout << "Введите имя владельца: ";
	std::cin >> ba.name;
	std::cout << "Введите баланс: ";
	std::cin >> ba.money;
	std::cout << "Введите новый баланс: ";
	double newMoney;
	std::cin >> newMoney;
	changeMoney(ba, newMoney);
	std::cout << "Ваш счёт: " << ba.name << ", " << ba.accountNum << ", " << ba.money << std::endl;
	
	return 0;
}

void changeMoney(bankAccount& b, const double newMoney) {
	b.money = newMoney;
}

