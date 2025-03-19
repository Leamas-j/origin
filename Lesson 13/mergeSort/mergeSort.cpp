#include <iostream>
#include "Windows.h"

int* merge(int* arr1, int size1, int* arr2, int size2);
int* merge_sort(int* arr, int size);
void printArr(int* arr, int size);

int main()
{
    SetConsoleOutputCP(1251); 

    int size[3]{10,15,18};

    int** arrAll = new int*[3];
    arrAll[0] = new int[size[0]]{ 3, 43, 38, 29, 18, 72, 57, 61, 2, 33 };    
    arrAll[1] = new int[size[1]]{ 88, 91, 87, 59, 53, 49, 29, 16, 4, 27, 28, 89, 2, 25 ,74 };   
    arrAll[2] = new int[size[2]] { 24, 66, 20, 79, 30, 16, 19, 62, 94, 59, 0, 7, 59, 90, 84, 60, 95, 62 };

    int* arB;
    for (int i = 0; i < 3; ++i) {
        std::cout << "Исходный массив: ";
        printArr(arrAll[i], size[i]);
        arB = merge_sort(arrAll[i], size[i]);
        std::cout << "Отсортированный массив: ";
        printArr(arB, size[i]);
        delete[] arB; 
        std::cout << std::endl;
    }
    for (int i = 0; i < 3; ++i) {
        delete[] arrAll[i];
    }
    delete[] arrAll;
    return 0;
}

int* merge_sort(int* arr, int size) {
    if (size == 1) return arr;
    else {
        int s1 = static_cast<int>(size / 2);
        int s2 = size - s1;
        int* left, * right;
        left = merge_sort(arr, s1);
        right = merge_sort(&arr[s1], s2);
        return merge(left, s1, right, s2);
    }
}

void printArr(int* arr, int size) {
    for (int i = 0; i < size; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

int* merge(int* arrA, int sizeA, int* arrB, int sizeB) {
    int ia = 0, ib = 0, ic = 0;
    int sizeRes = sizeA + sizeB;
    int* arrRes = new int[sizeRes];
    while ((ia < sizeA) || (ib < sizeB)) {
        if (ia == sizeA) {
            arrRes[ic] = arrB[ib];
            ib++;
        }
        else if (ib == sizeB) {
            arrRes[ic] = arrA[ia];
            ia++;
        }
        else if (arrA[ia] <= arrB[ib]) {
            arrRes[ic] = arrA[ia];
            ia++;
        }
        else {
            arrRes[ic] = arrB[ib];           
            ib++;
        }
        ic++;
    }
    return arrRes;
}
