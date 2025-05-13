#include <iostream>
#include <set>
#include <map>

int main()
{
  std::multiset<char> mess{ 'H','e','l','l','o',' ','w','o','r','l','d','!','!' };
  std::set<char> unMess{ 'H','e','l','l','o',' ','w','o','r','l','d','!','!' };

  std::multimap<int, char, std::greater<int>> res;
  for (const auto& k : unMess) {
    res.insert(std::make_pair(mess.count(k), k));
  }
  for (const auto& k : res) {
    std::cout << k.second << ": " << k.first << std::endl;
  }
  return 0;
}
