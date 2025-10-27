#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <Windows.h>
 
void fillVector(std::vector<int> &v, const int size) {
 
  for (int i = 0; i < size; ++i) {
    v.push_back(std::rand() % 10);
  }  
}

void summVectors(const std::vector<int>& v1, const std::vector<int>& v2, std::vector<int>& vSum, const int begin, const int end) {
  
  for (int i = begin; i < end; ++i) {
    vSum.at(i) = v1.at(i) + v2.at(i);
  } 
}

int main()
{
  SetConsoleOutputCP(1251);

  std::vector<int> vecSize{ 1000, 10000, 100000, 1000000 };
  std::vector<int> threadsCount{ 1, 2 , 4 , 8, 16};

  std::vector<int> vector1;
  std::vector<int> vector2;  

  std::vector<std::thread> th;

  std::cout << "Количество аппаратных ядер - " << std::thread::hardware_concurrency() << std::endl << std::endl;
 
  for (const auto& t : vecSize) {
    std::cout << "\t\t" << t;
  }
  std::cout << std::endl << std::endl;

  for (int i = 0; i < threadsCount.size(); ++i) {

    std::cout << threadsCount.at(i) << " потоков -\t";

    for (int j = 0; j < vecSize.size(); ++j) {

      fillVector(vector1, vecSize.at(j));
      fillVector(vector2, vecSize.at(j));  

      std::vector<int> vectorSumm(vecSize.at(j));

      int step = vecSize.at(j) / threadsCount.at(i);
      int tail = vecSize.at(j) % threadsCount.at(i);

      auto begin = std::chrono::high_resolution_clock::now();

      for (int k = 0; k < vecSize.at(j); k += step) {
        int begin = k;
        if (tail) {
          ++k;
          --tail;
        }
        int end = k + step;

        th.push_back(std::thread(summVectors, std::ref(vector1), std::ref(vector2), std::ref(vectorSumm), begin, end));
      }

      auto stop = std::chrono::high_resolution_clock::now();

      std::chrono::duration<double, std::milli> duration = stop - begin;
      std::cout << duration.count() << "s" << "\t\t";

      for (auto &t : th) {
        t.join();
      }
    
      vector1.clear();
      vector2.clear();
      th.clear();
    }
    std::cout << std::endl;
  }
 
  return 0;
}

