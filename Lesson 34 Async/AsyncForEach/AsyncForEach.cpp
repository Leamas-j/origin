#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>
#include <random>
#include <future>

template<typename Iterator, typename Func>
void parallel_for_each(Iterator first, Iterator last, Func &func)
{
  auto size = std::distance(first, last);
  if (size < 10)
  {   
    std::for_each(first, last, func);
    return;
  }
  else
  {
    Iterator middle = first;
    std::advance(middle, size / 2);

    auto first_half = async(parallel_for_each<Iterator, Func>, first, middle, std::ref(func));

    parallel_for_each(middle, last, func);
  }
}

void print_vector(int n)
{
  std::cout << n << " ";
}

int main()
{
  std::random_device rd;
  std::mt19937 gen{ rd() };
  std::uniform_int_distribution<> dis(0, 100);

  std::vector<int> vec;

  for (int i = 0; i < 35; ++i) {
    vec.push_back(dis(gen));
  }

  parallel_for_each(vec.begin(), vec.end(), print_vector);

  std::cout << std::endl;

  return 0;
}
