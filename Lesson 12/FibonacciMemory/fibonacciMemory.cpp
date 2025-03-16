#include <iostream>
#include <Windows.h>

long long fibonacci(int n, long long* mass)
{
    if (mass[n] != 0) return mass[n];
    else if (n < 2) {
        mass[n] = n;
    }
    else {
        mass[n] = fibonacci(n - 2, mass) + fibonacci(n - 1, mass);
    }
    return mass[n];
}

int main() {
    SetConsoleOutputCP(1251);

    std::cout << "Введите число: ";
    int num{};
    std::cin >> num;
    long long* mass = new long long[num] {};
    std::cout << std::endl;
    for (int i = 0; i < num; ++i)
    {
        std::cout << fibonacci(i, mass) << " ";
    }
    return 0;
}


