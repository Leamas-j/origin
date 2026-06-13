#include "ini_parser.h"
#include <algorithm>
#include <cctype>

namespace ch {
  constexpr char comment = ';';
  constexpr char sectionBegin = '[';
  constexpr char sectionEnd = ']';
  constexpr char equalSign = '=';
}

ini_parser::ini_parser(const std::string& fileName) {
  std::ifstream fin(fileName);
  if (!fin) {
    throw std::runtime_error("Failed to open file " + fileName);
  }

  std::string line;
  std::string currentSection;
  unsigned int lineNum = 0;

  while (std::getline(fin, line)) {
    lineNum++;
   
    if (line.empty() || line[0] == ch::comment || is_only_whitespace(line))
      continue;

    if (line[0] == ch::sectionBegin) {
      size_t endPos = line.find(ch::sectionEnd);
      if (endPos == std::string::npos) {
        throw std::runtime_error("Incorrect syntax on line " + std::to_string(lineNum));
      }

      currentSection = line.substr(1, endPos - 1);     
      currentSection.erase(0, currentSection.find_first_not_of(" \t"));
      currentSection.erase(currentSection.find_last_not_of(" \t") + 1);

      data_[currentSection];
      continue;
    }

    if (!currentSection.empty()) {
      size_t eqPos = line.find(ch::equalSign);
      if (eqPos != std::string::npos) {
        std::string key = line.substr(0, eqPos);
        std::string value = line.substr(eqPos + 1);

        size_t commPos = value.find(ch::comment);
        if (commPos != std::string::npos) {
          value = value.substr(0, commPos);
        }

        key.erase(0, key.find_first_not_of(" \t"));
        key.erase(key.find_last_not_of(" \t") + 1);
        value.erase(0, value.find_first_not_of(" \t"));
        value.erase(value.find_last_not_of(" \t\r\n") + 1);

        if (value.empty()) {
          throw std::runtime_error("Empty value on line " + std::to_string(lineNum));
        }

        data_[currentSection][key] = value;
      }
    }
  }
}

std::string ini_parser::get_str_value(const std::string& section, const std::string& key) const {
  auto secIt = data_.find(section);
  if (secIt == data_.end()) {
    std::stringstream ss;
    ss << "Section '" << section << "' not found.\nAvailable sections:\n";
    for (const auto& s : data_) ss << "  " << s.first << "\n";
    throw std::runtime_error(ss.str());
  }

  auto keyIt = secIt->second.find(key);
  if (keyIt == secIt->second.end()) {
    std::stringstream ss;
    ss << "Key '" << key << "' not found in section '" << section << "'.\nAvailable keys:\n";
    for (const auto& k : secIt->second) ss << "  " << k.first << "\n";
    throw std::runtime_error(ss.str());
  }

  return keyIt->second;
}

bool ini_parser::is_only_whitespace(const std::string& str) {
  return std::all_of(str.begin(), str.end(), [](unsigned char c) {
    return std::isspace(c);
    });
}

std::string ini_parser::get_value(const std::string& section, const std::string& key) const {
  return get_str_value(section, key);
}