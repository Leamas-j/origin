#include <iostream>
#include <windows.h>

void print_dinamic_array(int* arr, int logical_size, int actual_size);
int* append_to_dinamic_array(int* arr, int& logical_size, int& actual_size, int elToApp);
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
    std::cout << "Динамический массив:  ";
    print_dinamic_array(arr, logical_size, actual_size);
    int elemToAdd;
    do {
        std::cout << "Введите элемент для добавления: ";
        std::cin >> elemToAdd;
        if (elemToAdd) {
            int* new_arr = append_to_dinamic_array(arr, logical_size, actual_size, elemToAdd);
            arr = new_arr;
            std::cout << "Динамический массив: ";
        }
        else {
            std::cout << "Спасибо! Ваш массив: ";
        }
        print_dinamic_array(arr, logical_size, actual_size);
    } while (elemToAdd);
    delete[] arr;
    return 0;
}

void print_dinamic_array(int* arr, int logical_size, int actual_size) {
    char emptyCell = '_';
    for (int i = 0; i < actual_size; ++i) {
        i < logical_size ? std::cout << arr[i] << " " : std::cout << emptyCell << " ";
    }
    std::cout << std::endl;
}

int* append_to_dinamic_array(int* arr, int& logical_size, int& actual_size, int elToApp) {
    if (logical_size == actual_size) {
        actual_size *= 2;
        int* new_arr = new int[actual_size];
        for (int i = 0; i < logical_size; ++i) {
            new_arr[i] = arr[i];
        }
        new_arr[logical_size] = elToApp;
        ++logical_size;
        delete[] arr;
        return new_arr;
    }
    else {
        arr[logical_size] = elToApp;
        ++logical_size;
        return arr;
    }
}







