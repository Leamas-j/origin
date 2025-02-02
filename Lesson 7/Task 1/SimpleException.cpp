#include <iostream>
#include <string>
#include <Windows.h>

int function(std::string str, int forbidden_length) {
	int length = str.length();
	if (length == forbidden_length) throw "Вы ввели слово запретной длинны! До свидания\n";
	return length;
}
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	std::cout << "Введите запретную длину: ";
	int len{};
	std::cin >> len;
	while (1) {
		std::cout << "Введите слово: ";
		std::string word;
		std::cin >> word;
		try {
			std::cout << "Длина слова \"" << word << "\" равна " << function(word, len) << std::endl;
		}
		catch (const char* err) {
			std::cout << err << std::endl;
			break;
		}
	}
}
