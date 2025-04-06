#include <iostream>
#include <fstream>
#include "Windows.h"

void depth_first_search(int** graf, const int vertex, int* visited, const int vertexCount);
int main()
{
    SetConsoleOutputCP(1251);
    std::ifstream fin{ "input.txt" };
    int vertexCount;
    if (fin.is_open()) {
        fin >> vertexCount;
        int** graf = new int* [vertexCount];
        for (int i = 0; i < vertexCount; ++i) {
            graf[i] = new int[vertexCount];
        }
        for (int i = 0; i < vertexCount; ++i) {
            for (int j = 0; j < vertexCount; ++j) {
                fin >> graf[i][j];
            }
        }
        int* visitedVertex = new int[vertexCount] {0};
        std::cout << "Порядок обхода вершин: ";
        for (int i = 0; i < vertexCount; ++i) {
            if (!visitedVertex[i]) {
                depth_first_search(graf, i, visitedVertex, vertexCount);
            }
        }
        std::cout << std::endl;
        for (int i = 0; i < vertexCount; ++i) {
            delete[] graf[i];
        }
        delete[] graf;
        delete[] visitedVertex;
    }
    else {
        std::cout << "Не удалось открыть файл input.txt" << std::endl;
    }
}

void depth_first_search(int** graf, const int vertex, int* visited, const int vertexCount) {
    visited[vertex] = 1;
    std::cout << vertex + 1 << " ";
    for (int i = 0; i < vertexCount; ++i) {
        if (graf[i][vertex] == 1) {
            if (!visited[i]) {
                depth_first_search(graf, i, visited, vertexCount);
            }
        }
    }
}