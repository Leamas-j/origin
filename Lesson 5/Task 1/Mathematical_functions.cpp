// Mathematical_functions.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "Math_func.h"

enum math_op {
    addition = 1,
    subtraction,
    multiplication,
    division,
    exponentiation
};

int main()
{
    setlocale(LC_ALL, "RU");

    std::cout << "Введите первое число: ";
    double num1;
    std::cin >> num1;
    std::cout << "Введите второе число: ";
    double num2;
    std::cin >> num2;
    std::cout << "Выберите операцию (1 - сложение, 2 вычитание, 3 - умножение, 4 - деление, 5 - возведение в степень): ";
    int operation;
    std::cin >> operation;

    switch (operation) {
    case static_cast<int>(math_op::addition):
        std::cout << "Сумма " << num1 << " и " << num2 << " = " << summ(num1, num2) << std::endl;
        break;
    case static_cast<int>(math_op::subtraction):
        std::cout  << "Разность " << num1 << " и " << num2 << " = " << subtract(num1, num2) << std::endl;
        break;
    case static_cast<int>(math_op::multiplication):
        std::cout << "Произведение " << num1 << " и " << num2 << " = " << multiply(num1, num2) << std::endl;
        break;
    case static_cast<int>(math_op::division):
        std::cout << num1 << " деленное на " << num2 << " = " << divide(num1, num2) << std::endl;
        break;
    case static_cast<int>(math_op::exponentiation):
        std::cout << num1 << " в степени " << num2 << " = " << exponent(num1, num2) << std::endl;
        break;
    default:
        std::cout << "Неизвестная операция!" << std::endl;
    }  
}
