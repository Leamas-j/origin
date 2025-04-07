#include <iostream>
#include <fstream>
#include "Windows.h"

void depth_first_search(int** graph, const int vertex, int* visited, const int vertexCount);
int main()
{
    SetConsoleOutputCP(1251);
    std::ifstream fin{ "input.txt" };
    int vertexCount;
    if (fin.is_open()) {
        fin >> vertexCount;
        int** graph = new int* [vertexCount];
        for (int i = 0; i < vertexCount; ++i) {
            graph[i] = new int[vertexCount];
        }
        for (int i = 0; i < vertexCount; ++i) {
            for (int j = 0; j < vertexCount; ++j) {
                fin >> graph[i][j];
            }
        }
        fin.close();
        int* visitedVertex = new int[vertexCount] {0};
        std::cout << "Порядок обхода вершин: ";
        for (int i = 0; i < vertexCount; ++i) {
            if (!visitedVertex[i]) {
                depth_first_search(graph, i, visitedVertex, vertexCount);
            }
        }
        std::cout << std::endl;
        for (int i = 0; i < vertexCount; ++i) {
            delete[] graph[i];
        }
        delete[] graph;
        delete[] visitedVertex;
    }
    else {
        std::cout << "Не удалось открыть файл input.txt" << std::endl;
    }
}

void depth_first_search(int** graph, const int vertex, int* visited, const int vertexCount) {
    visited[vertex] = 1;
    std::cout << vertex + 1 << " ";
    for (int i = 0; i < vertexCount; ++i) {
        if (graph[i][vertex] == 1) {
            if (!visited[i]) {
                depth_first_search(graph, i, visited, vertexCount);
            }
        }
    }
}