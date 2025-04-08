#include <iostream>
#include <fstream>
#include "Windows.h"

int main()
{
    SetConsoleOutputCP(1251);
    std::ifstream fin{ "input.txt" };
    int vertexCount;
    if (fin.is_open()) {
        fin >> vertexCount;
        int** digraph = new int* [vertexCount];
        for (int i = 0; i < vertexCount; ++i) {
            digraph[i] = new int[vertexCount];
        }
        for (int i = 0; i < vertexCount; ++i) {
            for (int j = 0; j < vertexCount; ++j) {
                fin >> digraph[i][j];
            }
        }
        fin.close(); 
        std::cout << "Текстовый вид орграфа:\n";
        for (int i = 0; i < vertexCount; ++i) {
            bool findArc{ false };
            std::cout << i + 1 << ": ";
            for (int j = 0; j < vertexCount; ++j) {
                if (digraph[i][j] == 1) {
                    findArc = true;
                    std::cout << j + 1 << " ";
                }                    
            }
            if (!findArc) {
                std::cout << "нет";
            } 
            std::cout << std::endl;
        }
       
        std::cout << std::endl;
        for (int i = 0; i < vertexCount; ++i) {
            delete[] digraph[i];
        }
        delete[] digraph;
    }
    else {
        std::cout << "Не удалось открыть файл input.txt" << std::endl;
    }
}
