
#include <iostream>
#include <thread>
#include <chrono>
#include <windows.h>
#include <mutex>
#include <vector>

#define BLACK_WHITE (0 << 4 | 15)
#define WHITE_BLACK (15 << 4 | 0)
#define RED_BLACK (4 << 4 | 0)

std::mutex mt;

void progressBar(int x, int y, int num, int SBlength)
{
  HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD point; 
  point.X = x;
  point.Y = y + num;     

  std::unique_lock<std::mutex> lk(mt);

  SetConsoleTextAttribute(hStdOut, BLACK_WHITE);
  SetConsoleCursorPosition(hStdOut, point);  
  
  std::cout << num << " " << std::this_thread::get_id() << " ";

  lk.unlock(); 

  auto start = std::chrono::high_resolution_clock::now();

  for (int i = 0; i < SBlength; i++) 
  {    
    srand(time(NULL)*i);
    int slp = rand() % 100;
    lk.lock();
    try {
      
      std::this_thread::sleep_for(std::chrono::milliseconds(slp));     
      point.X = x + i + 10;
      point.Y = y + num;
      SetConsoleCursorPosition(hStdOut, point); 
      SetConsoleTextAttribute(hStdOut, WHITE_BLACK);
      if (slp < 5) throw 0;
    }
    catch (int k) {
      SetConsoleTextAttribute(hStdOut, RED_BLACK);
    }  
    std::cout << " ";
    

    lk.unlock(); 
  }

  

  auto stop = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> duration = stop - start;
 
  point.X = x + 20 + SBlength;
  point.Y = y + num; 

  lk.lock();

  SetConsoleTextAttribute(hStdOut, BLACK_WHITE);
  SetConsoleCursorPosition(hStdOut, point);

  std::cout <<  duration.count() << "ms";

  lk.unlock();
 
}
int main()
{
  SetConsoleOutputCP(1251);

  std::vector<std::thread> th;

  int x = 0;
  int y = 1;

  int numThreads = 5;
  int SBLen = 50;

  std::cout << "N " << "id";

  COORD p;
  p.X = 10;
  p.Y = 0;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
  std::cout << "StatusBar";

  p.X = SBLen + 20;
  p.Y = 0;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
  std::cout << "Time";
  
  for (int i = 0; i < numThreads; i++)
  {
    th.push_back(std::thread(progressBar, x, y, i, SBLen));
  }
  for (auto &t : th)
  {
    t.join();
  }
 
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
  p.X = 0;
  p.Y = numThreads+2;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);

  return 0;
}

