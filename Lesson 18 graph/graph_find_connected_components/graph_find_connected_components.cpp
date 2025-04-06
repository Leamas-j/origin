#include <iostream>
#include <fstream>
#include <vector>
#include "Windows.h"

void depth_first_search(int** graf, const int vertex, std::vector<int> &visited, const int vertexCount, int* components, int& comp);
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
        
        std::vector<int> visitedVertex;
        int* connectedComponent = new int[vertexCount] { 0 };
        int conComp{ 0 };
        
        std::cout << "Порядок обхода вершин: ";
        for (int i = 0; i < vertexCount; ++i) {
            if (!connectedComponent[i]) {
                ++conComp;
                depth_first_search(graf, i, visitedVertex, vertexCount, connectedComponent, conComp);
               
            }
        } 
        std::cout << std::endl;
        for (int k : visitedVertex) {
             std::cout << k+1 << " - " << connectedComponent[k] << std::endl;
        }
        std::cout << "Количество компонентов связности в графе: " << conComp;
        std::cout << std::endl;
        for (int i = 0; i < vertexCount; ++i) {
            delete[] graf[i];
        }
        delete[] graf;
        delete[] connectedComponent;
    }
    else {
        std::cout << "Не удалось открыть файл input.txt" << std::endl;
    }
}

void depth_first_search(int** graf, const int vertex, std::vector<int> &visited, const int vertexCount, int* components, int& comp) {
    visited.push_back(vertex);
    components[vertex] = comp;
    for (int i = 0; i < vertexCount; ++i) {
        if (graf[i][vertex] == 1) {
            if (!components[i]) {
                depth_first_search(graf, i, visited, vertexCount, components, comp);
            }
        }
    }
}