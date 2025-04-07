#include <iostream>
#include <fstream>
#include "Windows.h"

bool depth_first_search_cycle(int** graph, int vertex, int* visited, const int vertexCount, int& prev);
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
        int* visitedVertex = new int[vertexCount] { 0 };
        int start{ 0 }, prev{ 0 };
        depth_first_search_cycle(graph, start, visitedVertex, vertexCount, start);
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

bool depth_first_search_cycle(int** graph, int vertex, int* visited, const int vertexCount, int& prev) {
    visited[vertex] = 1;
    for (int i = 0; i < vertexCount; ++i) {
        if (graph[i][vertex] == 1) {
            if (visited[i]) {
                if (i != prev) {
                    std::cout << "В графе есть цикл!\n";
                    return true;
                }
            }
            else {
                if (depth_first_search_cycle(graph, i, visited, vertexCount, vertex)) {
                    return true;
                }
            }
        }
    }
    std::cout << "В графе нет циклов\n";
}