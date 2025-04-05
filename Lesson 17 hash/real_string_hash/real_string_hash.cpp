#include <iostream>
#include <cmath>
#include "Windows.h"

int real_string_hash(const std::string& s, const int p, const int n);
int main()
{
    SetConsoleOutputCP(1251);
    std::string str;
    std::cout << "Введите p: ";
    int p{};
    std::cin >> p;
    std::cout << "Введите n: ";
    int n{};
    std::cin >> n;
    do {
        std::cout << "Введите строку: ";
        std::cin >> str;
        std::cout << "Хэш строки " << str << " = " << real_string_hash(str, p, n) << std::endl;
    } while (str != "exit");
    return 0;
}

int real_string_hash(const std::string& s, const int p, const int n) {
    uint64_t tmpHash{ 0 };
    for (uint64_t i = 0; i < s.size(); ++i) {
        tmpHash += pow(p, i) * static_cast<uint64_t>(s[i]);
    }
    return tmpHash % n;
}
