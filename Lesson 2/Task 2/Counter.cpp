// Counter.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <Windows.h>

class Counter {
    int num;
public:
    Counter(int num){
        this->num = num;
    }
    Counter() {
        num = 1;
    }
    void incr() {
        ++num;
    }
    void decr() {
        --num;
    }
    int current() {
        return num;
    }
};

namespace operation {
    char increase = '+';
    char decrease = '-';
    char currentMeaning = '=';
    char exit_ing = 'x';
    char exit_rus = 'х';
} 

int main()
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    Counter* counter;

    std::cout << "Вы хотите указать начальное значение счётчика? Введите да или нет: ";
    std::string answer;
    std::cin >> answer;
    if (answer == "да") {
        std::cout << "Введите начальное значение счётчика: ";
        int initialValue;
        std::cin >> initialValue;
        counter = new Counter(initialValue);
    }
    else  counter = new Counter;
    char command;
    do {
        std::cout << "Введите команду('+', '-', '=' или 'x') : ";        
        std::cin >> command;
        if (command == operation::increase) {
            counter->incr();
        }
        else if (command == operation::decrease) {
            counter->decr();
        }
        else if(command == operation::currentMeaning) {
            std::cout << counter->current() << std::endl;
        }
        else if((command == operation::exit_ing) || (command == operation::exit_rus)) {
            std::cout << "До свидания!" << std::endl;
        }
    } while ((command != operation::exit_ing) && (command != operation::exit_rus));

    delete counter;
    return 0;
}

