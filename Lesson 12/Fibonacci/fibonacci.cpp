#include <iostream>
#include <Windows.h>

int fibonacci(int n)
{
    return n < 2 ? n : fibonacci(n - 2) + fibonacci(n - 1);
}

int main(){
    SetConsoleOutputCP(1251);
    std::cout << "Введите число: ";
    int num{};
    std::cin >> num;    

    for (int i = 0; i < num; ++i)
    {
        std::cout << fibonacci(i) << " ";
    }
    return 0;
}


