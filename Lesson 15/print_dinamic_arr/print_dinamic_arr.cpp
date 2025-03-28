#include <iostream>
#include <windows.h>

void print_dinamic_array(int* arr, int logical_size, int actual_size);

int main()
{
    SetConsoleOutputCP(1251);
    int actual_size, logical_size;
    do {
        std::cout << "Введите фактический размер массива: ";
        std::cin >> actual_size;
        std::cout << "Введите логический размер массива: ";
        std::cin >> logical_size;
        if (logical_size > actual_size) {
            std::cout << "Ошибка! Логичесий размер массива не может превышать фактический!" << std::endl;
        }
    } while (logical_size > actual_size);
    int* arr = new int[actual_size];
    for (int i = 0; i < logical_size; ++i) {
        std::cout << "Введите arr[" << i << "]: ";
        std::cin >> arr[i];
    }
    print_dinamic_array(arr, logical_size, actual_size);
    delete[] arr;
    return 0;
}

void print_dinamic_array(int* arr, int logical_size, int actual_size) {
    char emptyCell = '_';
    std::cout << "Динамический массив: ";
    for (int i = 0; i < actual_size; ++i) {
        i < logical_size ? std::cout << arr[i] << " " : std::cout << emptyCell << " ";
    }
}
