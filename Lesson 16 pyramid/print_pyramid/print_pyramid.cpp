#include <iostream>
//#include <cmath>

#include <Windows.h>

void print_pyramid(int* arr, const int size);
int main()
{
    SetConsoleOutputCP(1251);
    /*
    const int SIZE = 6;
    int pyramid[SIZE]{ 1, 3, 6, 5, 9, 8 };
 */
 /*
    const int SIZE = 8;
    int pyramid[SIZE]{ 94, 67, 18, 44, 55, 12, 6, 42};
*/
    const int SIZE = 10;
    int pyramid[SIZE]{ 16, 11, 9, 10, 5, 6, 8, 1, 2, 4 };

    std::cout << "Исходный массив: ";
    for (int i = 0; i < SIZE; ++i) {
        std::cout << pyramid[i] << " ";
    }
    std::cout << std::endl;
    print_pyramid(pyramid, SIZE);
}

void print_pyramid(int* arr, const int size) {
    int level{ 0 };
    std::cout << "Пирамида:\n";
    for (int i = 0; i < size; ++i) {
        level = static_cast<int>(log2(i + 1));
        std::cout << level;
        if (level) {
            (i - 1) % 2 == 0 ? std::cout << " left" : std::cout << " right";
            std::cout << "(" << arr[static_cast<int>((i - 1) / 2)] << ") ";
        }
        else {
            std::cout << " root ";
        }
        std::cout << arr[i] << std::endl;
    }    
}
