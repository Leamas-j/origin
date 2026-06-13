#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <stdexcept>

class ini_parser {
private:
  std::map<std::string, std::map<std::string, std::string>> data_;

  std::string get_str_value(const std::string& section, const std::string& key) const;

public:
  ini_parser(const std::string& fileName);

  bool is_only_whitespace(const std::string& str);

  template <typename T>
  T get_value(const std::string& section, const std::string& key) const {
    std::string strValue = get_str_value(section, key);
    std::stringstream ss(strValue);
    T result{};

    if (!(ss >> result)) {
      throw std::runtime_error("Failed to convert to requested type");
    }

    char remaining{};
    if (ss >> remaining) {
      throw std::runtime_error("Extra characters in input string");
    }
    return result;
  }
  
  std::string get_value(const std::string& section, const std::string& key) const;
};