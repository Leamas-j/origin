#include <iostream>

#define MODE 1

#ifndef MODE 
	#error Необходимо определить MODE!
#elif MODE == 1
	double add(double a, double b) {
		return a + b;
}
#endif	

int main()
{
	setlocale(LC_ALL, "RU");

#if !MODE 
	std::cout << "Работаю в режиме тренировки\n";
#elif MODE == 1
	std::cout << "Работаю в боевом режиме\n";
	std::cout << "Введите число 1: ";
	double num1{};
	std::cin >> num1;
	std::cout << "Введите число 2: ";
	double num2{};
	std::cin >> num2;
	std::cout << "Результат сложения: " << add(num1, num2) << std::endl;
#else
	std::cout << "Неизвестный режим.\nЗавершение работы." << std::endl;
#endif
}
