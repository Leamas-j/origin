#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <boost/locale.hpp>
#include "Windows.h"

#include "../Shared/ini_parser.h"
#include "../Shared/database.h"
#include "../Shared/string_modify.h"

int main()
{ 
  SetConsoleCP(1251);
  SetConsoleOutputCP(1251);

  boost::locale::generator gen;
  std::locale loc = gen("ru_RU.UTF-8");

  try
  {
    ini_parser parser("config.ini");

    std::string conn_str = "host = " + parser.get_value("DataBase", "host") +
      " port = " + parser.get_value("DataBase", "port") +
      " dbname = " + parser.get_value("DataBase", "dbname") +
      " user = " + parser.get_value("DataBase", "user") +
      " password = " + parser.get_value("DataBase", "password");

    DataBase db(conn_str);

    while(1)
    {      
      std::cout <<  "\nВведите слова для поиска (не более 4).\nДля выхода введите \"exit\"." << std::endl;
      std::string str_for_search{};   
      std::getline(std::cin, str_for_search);     

      if (str_for_search == "exit") break;
      
      std::wstring wideData;
      wideData = String_modify::to_wstring(str_for_search);
      std::wstring resultWide{};

      for (wchar_t ch : wideData) {
        if (std::isalpha(ch, loc)) {
          resultWide += ch;
        }
        else {
          resultWide += L' ';
        }
      }

      std::wistringstream wiss(resultWide);
      std::vector<std::string> words{};
      std::wstring wword; 

      std::cout << "Ищем слова: ";
      while (wiss >> wword)
      {
        if (wword.size() < 3 || wword.size() > 32) continue;

        if (words.size() >= 4) break;
      
        std::string utf8_word = String_modify::wstring_to_utf8(wword);

        std::string lower_word = boost::locale::to_lower(utf8_word, loc);

        words.push_back(lower_word);
        std::cout << String_modify::utf8_to_cp1251(lower_word) << ' ';
      }
      std::cout << std::endl;

      auto searchResults = db.selectDocuments(words);

      if (searchResults.empty())
      {
        std::cout << "Не удалось найти документы, содержащие все введенные слова!" << std::endl;
        continue;
      }

      std::cout << "Документы, содержащие все введенные слова, и их релевантность:" << std::endl;

      for (const auto& item : searchResults)
      {
        std::cout << String_modify::utf8_to_cp1251(item.name) << ' ' << item.relevance << std::endl;
      }

      std::cout << std::endl;
    }
  }
  catch (const std::exception& e)
  {
    std::cout << e.what();
    return EXIT_FAILURE;
  }
  return 0;
}