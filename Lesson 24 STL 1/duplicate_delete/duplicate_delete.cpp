#include <iostream>
#include <set>

int main()
{
  std::set<int, std::greater<int>> mySet;
  int setCount;
  std::cin >> setCount;
  int setNum;
  for (int i = 0; i < setCount; ++i) {
    std::cin >> setNum;
    mySet.insert(setNum);
  }
  std::cout << std::endl;
  for (const int& k : mySet) {
    std::cout << k << std::endl;
  }
  return 0;
}
