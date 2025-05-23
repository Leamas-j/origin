﻿#include <iostream>
#include <fstream>
#include <queue>
#include "Windows.h"

void breadth_first_search(int** graph, int vertex, int* visited, const int vertexCount);
int main()
{
    SetConsoleOutputCP(1251);
    std::ifstream fin{ "input.txt" };
    int vertexCount;
    if (fin.is_open()) {
        fin >> vertexCount;
        int begin;
        do {
            std::cout << "В графе 7 вершин. Введите номер вершины, с которой начнётся обход: ";
            std::cin >> begin;
        } while ((!begin) || (begin > 7));
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
        breadth_first_search(graph, begin - 1, visitedVertex, vertexCount);
        for (int i = 0; i < vertexCount; ++i) {
            if (!visitedVertex[i]) {
                breadth_first_search(graph, i, visitedVertex, vertexCount);
            }
        }
        std::cout << std::endl;
        for (int i = 0; i < vertexCount; ++i) {
            delete[] graph[i];
        }
        delete[] graph;
    }
    else {
        std::cout << "Не удалось открыть файл input.txt" << std::endl;
    }
}
void breadth_first_search(int** graph, int vertex, int* visited, const int vertexCount) {
    std::queue <int> que;
    que.push(vertex);
    visited[vertex] = 1;   
    while (!que.empty()) {
        int v = que.front();
        std::cout << v + 1 << " ";
        que.pop();
        for (int i = 0; i < vertexCount; ++i) {
            if (graph[v][i] == 1) {
                if (!visited[i]) {
                    visited[i] = 1;                    
                    que.push(i);
                }
            }
        }        
    }   
}