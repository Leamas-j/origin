#include <iostream>
#include <windows.h>

void print_dinamic_array(int* arr, int logical_size, int actual_size);
int* remove_dinamic_array_head(int* arr, int& logical_size, int& actual_size);
int main()
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

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
    std::string answer;
    do {
        std::cout << "Удалить первый элемент? ";
        std::cin >> answer;
        if (answer == "да") {
            if (actual_size) {
                int* new_arr = remove_dinamic_array_head(arr, logical_size, actual_size);
                arr = new_arr;
                std::cout << "Динамический массив: ";
            }
            else {
                std::cout << "Невозможно удалить первый элемент, так как массив пустой. До свидания!";
                break;
            }
        }
        else {
            std::cout << "Спасибо! Ваш динамический массив: ";
        }
        print_dinamic_array(arr, logical_size, actual_size);
    } while (answer == "да");
    delete[] arr;
    return 0;
}

void print_dinamic_array(int* arr, int logical_size, int actual_size) {
    char emptyCell = '_';
    if (!actual_size) {
        std::cout << emptyCell;
    }
    else {
        for (int i = 0; i < actual_size; ++i) {
            i < logical_size ? std::cout << arr[i] << " " : std::cout << emptyCell << " ";
        }
    }
    std::cout << std::endl;
}

int* remove_dinamic_array_head(int* arr, int& logical_size, int& actual_size) {
    --logical_size;
    if (logical_size <= static_cast<int>(actual_size / 3)) {
        actual_size /= 3;
        int* new_arr = new int[actual_size];
        for (int i = 0; i < logical_size; ++i) {
            new_arr[i] = arr[i + 1];
        }
        delete[] arr;
        return new_arr;
    }
    else {
        for (int i = 0; i < logical_size; ++i) {
            arr[i] = arr[i + 1];
        }
        return arr;
    }
}







