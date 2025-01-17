// Calculator.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <Windows.h>

class Calculator {
    double num1;
    double num2;
public:
    double add() {
        return num1 + num2;
    }
    double multiply() {
        return num1 * num2;
    }
    double subtract_1_2() {
        return num1 - num2;
    }
    double subtract_2_1() {
        return num2 - num1;
    }
    double divide_1_2() {
        return num1 / num2;
    }
    double divide_2_1() {
        return num2 / num1;
    }
    bool set_num1(double num1) {
        if (num1 != 0) {
            this->num1 = num1;
            return true;
        }
        else return false;       
    }
    bool set_num2(double num2) {
        if (num2 != 0) {
            this->num2 = num2;
            return true;
        }
        else return false;
    }
};

int main()
{
    SetConsoleOutputCP(1251);

    while (1) {
        Calculator calc;
        bool set_num;
        do {            
            std::cout << "Введите num1: ";
            double num1;
            std::cin >> num1;
            set_num = calc.set_num1(num1);
            if (!set_num) std::cout << "Неверный ввод!" << std::endl;
        } while (!set_num);
        do {            
            std::cout << "Введите num2: ";
            double num2;
            std::cin >> num2;
            set_num = calc.set_num2(num2);
            if (!set_num) std::cout << "Неверный ввод!" << std::endl;
        } while (!set_num);
        std::cout << "num1 + num2 = " << calc.add() << std::endl; 
        std::cout << "num1 - num2 = " << calc.subtract_1_2() << std::endl;
        std::cout << "num2 - num1 = " << calc.subtract_2_1() << std::endl; 
        std::cout << "num2 * num1 = " << calc.multiply() << std::endl;
        std::cout << "num1 / num2 = " << calc.divide_1_2() << std::endl;
        std::cout << "num2 / num1 = " << calc.divide_2_1() << std::endl;   
    }
    return 0;
}
