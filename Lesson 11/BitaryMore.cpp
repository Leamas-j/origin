#include <iostream>
#include "windows.h"

int main()
{
    SetConsoleOutputCP(1251);
    const int SIZE = 9;
    int mass[SIZE] = { 14, 16, 19, 32, 32, 32, 56, 69, 72 };
    std::cout << "Введите точку отсчета: ";
    int point{};
    std::cin >> point;

    int left{ 0 };
    int right{ SIZE - 1 };
    int middle{ 0 };

    while (left <= right) {
        middle = (left + right) / 2;
        if (mass[middle] > point) {
            right = middle - 1;
        }
        else {
            left = middle + 1;
        }
    }
    std::cout << "Количество элементов в массиве больших, чем " << point << ": " << SIZE - left << std::endl;
    return 0;
}