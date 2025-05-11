#include <iostream>

class Functor {
  unsigned m_sum;
  unsigned m_counter;   
  int arr[6]{ 4, 1, 3, 6, 25, 54 };
public:
  Functor() : m_sum{ 0 }, m_counter{ 0 } {   
  }
  void operator()() { 
    for (int k : arr) {
      if (k % 3 == 0) {
        m_sum += k;
        ++m_counter;
      }
    }
  }
  unsigned get_sum() {
    return m_sum;
  }
  unsigned get_count() {
    return m_counter;
  }
};
int main() {
  Functor f;
  f();
  std::cout << "get_sum() = " << f.get_sum() << std::endl;
  std::cout << "get_count() = " << f.get_count() << std::endl;
  return 0;
}