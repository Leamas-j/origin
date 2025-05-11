#include <iostream>
#include <vector>

template <class T>
T squaring(T a) {
  return a * a;
}

template<class T>
std::vector<T> squaring(const std::vector<T>& a) {
  std::vector<T> result;
  for (T k : a) {
    result.push_back(squaring(k));
  }
  return result;
}

int main()
{
  int num{ 4 };
  std::cout << squaring(num) << std::endl;
  std::vector<int> vec{-1, 4, 8};
  std::vector<int> res = squaring(vec);
  for (int k : res) {
    std::cout << k << " ";
  }
}
