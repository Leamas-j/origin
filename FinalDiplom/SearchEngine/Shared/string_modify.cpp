#include <codecvt>
#include <iostream>
#include <vector>
#include "windows.h"

#include "string_modify.h"

std::wstring String_modify::to_wstring(const std::string& str)
{
  try {
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    return converter.from_bytes(str);
  }
  catch (const std::range_error& e)
  {
    int size_needed = MultiByteToWideChar(1251, 0, str.c_str(), (int)str.size(), NULL, 0);
    std::wstring result(size_needed, 0);
    MultiByteToWideChar(1251, 0, str.c_str(), (int)str.size(), &result[0], size_needed);
    return result;
  }
  catch (const std::exception& e)
  {
    std::cerr << "Ñonversion error: " << e.what() << std::endl;
    return L"";
  }
}

std::string String_modify::wstring_to_utf8(const std::wstring& wstr)
{
  try {
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    return converter.to_bytes(wstr);
  }
  catch (const std::exception& e) {
    std::cerr << "wstring_to_utf8 conversion error: " << e.what() << std::endl;
    return "";
  }
}

std::string String_modify::utf8_to_cp1251(std::string const& utf8)
{
  if (!utf8.empty())
  {
    int wchlen = MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), utf8.size(), NULL, 0);
    if (wchlen > 0 && wchlen != 0xFFFD)
    {
      std::vector<wchar_t> wbuf(wchlen);
      int result_u = MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), utf8.size(), &wbuf[0], wchlen);
      if (!result_u) {
        throw std::runtime_error("utf8_to_cp1251 cannot convert MultiByteToWideChar!");
      }
      std::vector<char> buf(wchlen);
      int result_c = WideCharToMultiByte(1251, 0, &wbuf[0], wchlen, &buf[0], wchlen, 0, 0);
      if (!result_c) {
        throw std::runtime_error("utf8_to_cp1251 cannot convert WideCharToMultiByte!");
      }

      return std::string(&buf[0], wchlen);
    }
  }
  return std::string();
}

std::string String_modify::cp1251_to_utf8(const std::string& cp1251) 
{
  if (cp1251.empty()) return "";

  int result_u = MultiByteToWideChar(1251, 0, cp1251.c_str(), -1, NULL, 0);
  if (!result_u) 
  {
    throw std::runtime_error("cp1251_to_utf8 cannot convert MultiByteToWideChar!");
  }

  std::vector<wchar_t> ures(result_u);
  if (!MultiByteToWideChar(1251, 0, cp1251.c_str(), -1, ures.data(), result_u))
  {
    throw std::runtime_error("cp1251_to_utf8 cannot convert MultiByteToWideChar 2!");
  }

  int result_c = WideCharToMultiByte(CP_UTF8, 0, ures.data(), -1, NULL, 0, NULL, NULL);
  if (!result_c) 
  {
    throw std::runtime_error("cp1251_to_utf8 cannot convert WideCharToMultiByte!");
  }

  std::vector<char> cres(result_c);
  if (!WideCharToMultiByte(CP_UTF8, 0, ures.data(), -1, cres.data(), result_c, NULL, NULL)) 
  {
    throw std::runtime_error("cp1251_to_utf8 cannot convert WideCharToMultiByte 2!");
  }

  return std::string(cres.data());
}
