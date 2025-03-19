#include <iostream>
#include <Windows.h>

void count_sort(int* arr, int size);
void printArr(int* arr, int size);

int main()
{
    SetConsoleOutputCP(1251);
   
    int size[3]{30,40,45 };

    int** arrAll = new int* [3];
    arrAll[0] = new int[size[0]] { 19, 14, 22, 22, 17, 22, 13, 21, 20, 24, 18, 10, 17, 16, 17, 20, 22, 11, 20, 16, 14, 13, 10, 22, 18, 14, 16, 24, 19, 17 };
    arrAll[1] = new int[size[1]] { 16, 17, 14, 20, 22, 20, 17, 22, 16, 19, 23, 24, 20, 22, 21, 18, 14, 16, 17, 21, 10, 11, 19, 23, 11, 11, 17, 17, 11, 21, 17, 11, 17, 16, 12, 11, 16, 22, 23, 16 };
    arrAll[2] = new int[size[2]] { 21, 15, 19, 18, 23, 12, 18, 18, 19, 23, 12, 20, 15, 22, 21, 18, 19, 20, 12, 16, 20, 14, 17, 13, 10, 23, 19, 14, 10, 22, 19, 12, 24, 23, 22, 15, 13, 22, 18, 18, 11, 23, 24, 17, 10 };
       
    for (int i = 0; i < 3; ++i) {  
        std::cout << "Исходный массив: ";
        printArr(arrAll[i], size[i]);
        count_sort(arrAll[i], size[i]);
        std::cout << "Отсортированный массив: ";
        printArr(arrAll[i], size[i]);
        std::cout << std::endl;
    }
    for (int i = 0; i < 3; ++i) {
        delete[] arrAll[i];
    }
    delete[] arrAll;
    return 0;
}
void printArr(int* arr, int size) {
    for (int i = 0; i < size; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}
void count_sort(int* arr, int size) {
    int tmpSize = 15;
    int* tmpArr = new int[tmpSize] {};
    for (int i = 0; i < size; ++i) {
        tmpArr[arr[i] - 10]++;        
    }

    for (int i = 0, k = 0; i < tmpSize; ++i) {
        for (int j = 0; j < tmpArr[i]; ++j) {
            arr[k] = i + 10;
            ++k;
        }
    }
    delete[] tmpArr;
}
