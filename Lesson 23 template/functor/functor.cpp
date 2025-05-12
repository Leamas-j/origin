#include <iostream>

class Functor {
  unsigned m_sum;
  unsigned m_counter; 
public:
  Functor() : m_sum{ 0 }, m_counter{ 0 } {   
  }
  void operator()(int k) { 
    if (k % 3 == 0) {
      m_sum += k;
      ++m_counter;
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
  f( 4 );
  f( 1 );
  f( 3 );
  f( 6 );
  f( 25 );
  f( 54 );
  std::cout << "get_sum() = " << f.get_sum() << std::endl;
  std::cout << "get_count() = " << f.get_count() << std::endl;
  return 0;
}