#include <iostream>
#include <vector>

#include "Windows.h"

std::vector<int> merge(std::vector<int> arr1, int size1, std::vector<int> arr2, int size2);
std::vector<int> merge_sort(std::vector<int> arr, int size);
void printArr(std::vector<int>arr);

int main()
{
    SetConsoleOutputCP(1251);
    /*
        const int size{10};
        int arr[size]{ 3, 43, 38, 29, 18, 72, 57, 61, 2, 33 };
    */
    /*
       const int size{15};
       int arr[size]{ 88, 91, 87, 59, 53, 49, 29, 16, 4, 27, 28, 89, 2, 25 ,74 };
    */
    const int size{ 18 };
    int arr[size]{ 24, 66, 20, 79, 30, 16, 19, 62, 94, 59, 0, 7, 59, 90, 84, 60, 95, 62 };

    std::vector<int> arrA;
    for (int i = 0; i < size; ++i) {
        arrA.push_back(arr[i]);
    }
    std::vector<int> arB;

    std::cout << "Исходный массив: ";
    printArr(arrA);
    arB = merge_sort(arrA, size);
    std::cout << "Отсортированный массив: ";
    printArr(arB);
    std::cout << std::endl;
    return 0;
}

std::vector<int> merge_sort(std::vector<int> arr, int size) {
    if (size == 1) return arr;
    else {
        int s1 = static_cast<int>(size / 2);
        int s2 = size - s1;
        std::vector<int> left, right;
        for (int i = 0; i < size; ++i) {
            if (i < s1) {
                left.push_back(arr.at(i));
            }
            else {
                right.push_back(arr.at(i));
            }
        }
        left = merge_sort(left, s1);
        right = merge_sort(right, s2);
        return merge(left, s1, right, s2);
    }
}

void printArr(std::vector<int> arr) {
    for (const auto v : arr) {
        std::cout << v << " ";
    }
    std::cout << std::endl;
}

std::vector<int> merge(std::vector<int> arrA, int sizeA, std::vector<int> arrB, int sizeB) {
    int ia = 0, ib = 0;
    std::vector<int> arrRes;
    while ((ia < sizeA) || (ib < sizeB)) {
        if (ia == sizeA) {
            arrRes.push_back(arrB.at(ib));
            ib++;
        }
        else if (ib == sizeB) {
            arrRes.push_back(arrA.at(ia));
            ia++;
        }
        else if (arrA.at(ia) <= arrB.at(ib)) {
            arrRes.push_back(arrA.at(ia));
            ia++;
        }
        else {
            arrRes.push_back(arrB.at(ib));
            ib++;
        }
    }
    return arrRes;
}
