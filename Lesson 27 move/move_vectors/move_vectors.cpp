#include <iostream>
#include <vector>
#include <utility>

template<typename T>
void move_vectors(std::vector<T>& source, std::vector<T>& destination) {
 
  if (&source != &destination) {
    
    destination = std::move(source);
   
    source.clear();
  }
}

int main()
{
  std::vector <std::string> one = { "test_string1", "test_string2" };
  std::vector <std::string> two;

  move_vectors<std::string>(one, two);

  for (const auto& str : two) {
    std::cout << str << " ";
  }
}

