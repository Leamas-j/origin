#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
  std::vector<int> vec = { 1, 1, 2, 5, 6, 1, 2, 4 };

  std::sort(begin(vec), end(vec));

  vec.erase(std::unique(begin(vec), end(vec)), end(vec));

  for (int k : vec) {
    std::cout << k << " ";
  }

  return 0;
}

