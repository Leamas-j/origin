#include <iostream>
#include <set>
#include <map>
#include <unordered_set>

int main()
{
  std::string str{ "Hello world!!" };
  std::multiset<char> mess{ str.begin(), str.end()};
  std::unordered_set<char> unMess{ mess.begin(), mess.end()};
  std::multimap<int, char, std::greater<int>> res;

  for (const auto& k : unMess) {
    res.insert(std::make_pair(mess.count(k), k));
  }

  for (const auto& k : res) {
    std::cout << k.second << ": " << k.first << std::endl;
  }

  return 0;
}
