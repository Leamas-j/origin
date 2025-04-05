#include <iostream>
#include "Windows.h"

int simple_string_hash(const std::string& s);
int main()
{
    SetConsoleOutputCP(1251);
    std::string str;
    do {
        std::cout << "Введите строку: ";
        std::cin >> str;
        std::cout << "Наивный хэш строки " << str << " = " << simple_string_hash(str) << std::endl;
    } while (str != "exit");
    return 0;
}

int simple_string_hash(const std::string& s) {
    int summ{ 0 };
    for (char c : s) {
        summ += static_cast<int>(c);
    }
    return summ;
}
