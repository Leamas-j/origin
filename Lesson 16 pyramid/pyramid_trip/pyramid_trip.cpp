#include <iostream>
#include "Windows.h"

void print_one_knot(int* arr, int knot);
void print_pyramid(int* arr, const int size);
bool findParent(const int child, int& parent);
bool findLeftChild(const int parent, int& child, const int size);
bool findRightChild(const int parent, int& child, const int size);

int main()
{
    SetConsoleOutputCP(1251);
    const int SIZE = 6;
    int pyramid[SIZE]{ 1, 3, 6, 5, 9, 8 };

    /*
       const int SIZE = 8;
       int pyramid[SIZE]{ 94, 67, 18, 44, 55, 12, 6, 42};
   *//*
       const int SIZE = 10;
       int pyramid[SIZE]{ 16, 11, 9, 10, 5, 6, 8, 1, 2, 4};
    */
    std::cout << "Исходный массив: ";
    for (int i = 0; i < SIZE; ++i) {
        std::cout << pyramid[i] << " ";
    }
    std::cout << std::endl;
    print_pyramid(pyramid, SIZE);
    std::string command;
    int position{ 0 };    
    do {
        std::cout << "Вы находитесь здесь: ";
        print_one_knot(pyramid, position);
      
        std::cout << "Введите команду: ";
        std::cin >> command;
        if (command == "up") {
            int pos{ position }, par{ 0 };
            bool up = findParent(pos, par);
            if (up) {
                std::cout << "Ok\n";
                position = par;
            }
            else {
                std::cout << "Ошибка! Отсутствует родитель\n";
            }
        }
        else if (command == "left") {
            int pos{ position }, ch{ 0 };
            bool left = findLeftChild(pos, ch, SIZE);
            if (left) {
                std::cout << "Ok\n";
                position = ch;
            }
            else {
                std::cout << "Ошибка! Отсутствует левый потомок\n";
            }
        }
        else if (command == "right") {
            int pos{ position }, ch{ 0 };
            bool right = findRightChild(pos, ch, SIZE);
            if (right) {
                std::cout << "Ok\n";
                position = ch;
            }
            else {
                std::cout << "Ошибка! Отсутствует правый потомок\n";
            }
        }
        else if (command != "exit") {
            std::cout << "Введена неверная команда!" << std::endl;
        }
    }

    while (command != "exit");

}
void print_one_knot(int* arr, int knot) { 
    int level = static_cast<int>(log2(knot + 1));
    std::cout << level;
    if (level) {
        (knot - 1) % 2 == 0 ? std::cout << " left" : std::cout << " right";
        std::cout << "(" << arr[static_cast<int>((knot - 1) / 2)] << ") ";
    }
    else {
        std::cout << " root ";
    }
    std::cout << arr[knot] << std::endl;
}

void print_pyramid(int* arr, const int size) {
   
    std::cout << "Пирамида:\n";
    for (int i = 0; i < size; ++i) {
        print_one_knot(arr, i);
    }
}

bool findParent(const int child, int& parent) {
    if (!child) return false;
    else {
        parent = (child - 1) / 2;
        return true;
    }
}
bool findLeftChild(const int parent, int& child, const int size) {
    int tmpChild = 2 * parent + 1;
    if (tmpChild >= size) return false;
    else {
        child = tmpChild;
        return true;
    }
}

bool findRightChild(const int parent, int& child, const int size) {
    int tmpChild = 2 * parent + 2;
    if (tmpChild >= size) return false;
    else {
        child = tmpChild;
        return true;
    }
}