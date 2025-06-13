#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <exception>
#include <windows.h>
#include <vector>

namespace ch {
  char comment = ';';
  char sectionBegin = '[';
  char sectionEnd = ']';
  char equalSign = '=';
}

class ini_parser {

private:

  std::string currSection_;
  std::ifstream fin_;
  unsigned int strCount_{};
  bool sectionIsFound_{ false };
  bool keyIsFount_{ false };

  std::map<std::string, std::vector<std::string>> mapSections_;

  std::string get_str_value(std::string section, std::string key) {
    std::string line;
    std::string returnValue{ "" };

    while (getline(fin_, line)) {

      strCount_++;

      if (line.empty() || line[0] == ch::comment) continue;
     
      if(is_only_whitespace(line)) continue;
      
      if (line[0] == ch::sectionBegin) {
        if(line.back() != ch::sectionEnd) throw std::runtime_error("Incorrect syntax on line " + std::to_string(strCount_));
        
        currSection_ = line.substr(1, line.size() - 2);

        currSection_.erase(0, currSection_.find_first_not_of(" "));
        currSection_.erase(currSection_.find_last_not_of(" \n\t") + 1);

        mapSections_[currSection_];
        
        if (currSection_ == section) sectionIsFound_ = true;

        continue;
      }

      if (currSection_ == section) {

        size_t delimiterPos = line.find(ch::equalSign);
        size_t commentPos = line.find(ch::comment);

        if (commentPos != line.size()) {
          line = line.substr(0, commentPos);
        }

        if (delimiterPos != line.size()) {
          std::string rKey = line.substr(0, delimiterPos);
          std::string rValue = line.substr(delimiterPos + 1);

          rKey.erase(0, rKey.find_first_not_of(" "));
          rKey.erase(rKey.find_last_not_of(" \n\t") + 1);  

          mapSections_[currSection_].push_back(rKey);
          
          if (rKey == key) {
            keyIsFount_ = true;

            rValue.erase(0, rValue.find_first_not_of(" "));
            rValue.erase(rValue.find_last_not_of(" \n\t") + 1);

            if (rValue.empty()) throw std::runtime_error("Incorrect syntax on line " + std::to_string(strCount_));

            returnValue = rValue;
          }
        }  
      }     
    } 
    if (!sectionIsFound_) throw std::runtime_error([&]() {
        std::stringstream ss;
        ss << "The " + section + " is not found.\nThere is sections:\n";       
        for (const auto& k : mapSections_) {
          ss << k.first;
          ss << "\n";
        }       
        return ss.str();
      }());

    if (mapSections_[section].empty()) throw std::runtime_error(section + " is empty");
   
    if (!keyIsFount_) throw std::runtime_error([&](){
      std::stringstream ss;
      ss << "The " + key + " is not found.\nThere is variables in " + section + ":\n";
     
      for (const auto& k : mapSections_[section]) {
        ss << k;
        ss << "\n";
      }     
      return ss.str();
      }());

    return returnValue;
  }

public:
  ini_parser(std::string fileName) {
    fin_.open(fileName);

    if (!fin_) {
      throw std::runtime_error("Failed to open file " + fileName);
    }
  }

  bool is_only_whitespace(const std::string& str) {
    for (const char& c : str) {
      if (!std::isspace(static_cast<unsigned char>(c))) return false;
    }
    return true;
  }

  template <typename T>
  T get_value(std::string section, std::string key) {

    std::string strValue = get_str_value(section, key);    

    std::stringstream ss(strValue);

    T result{};

    if (!(ss >> result)) {
      throw std::runtime_error("Filed to convert to requested type");
    }
    
    char remaining{};

    if (ss >> remaining) {
      throw std::runtime_error("Extra characters in input string");
    }
   
    return result;
  }

  template <>
  std::string get_value(std::string section, std::string key) {

    std::string strValue = get_str_value(section, key);
    return strValue;
  }

};

int main()
{  
  SetConsoleOutputCP(1251);

  ini_parser parser("TextFile.ini");

  try {
    auto value = parser.get_value<float>("Section2", "var1");
    std::cout << value << std::endl;
  }
  catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }
  return 0;
}

