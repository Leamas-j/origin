#pragma once

#include <string>

namespace String_modify
{
  std::wstring to_wstring(const std::string& str);
  std::string wstring_to_utf8(const std::wstring& wstr);
  std::string utf8_to_cp1251(std::string const& utf8);
  std::string cp1251_to_utf8(const std::string& cp1251);
};
