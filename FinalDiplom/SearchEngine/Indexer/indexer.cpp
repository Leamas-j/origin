#include "indexer.h"
#include <cctype> 
#include <Windows.h>
#include <boost/locale.hpp>
#include "../Shared/string_modify.h"

constexpr unsigned char WHITESPACE = ' ';

namespace WordLength 
{
  constexpr size_t MIN_WORD_LENGTH = 3;
  constexpr size_t MAX_WORD_LENGTH = 32;
}

namespace Utf8Constants {
  constexpr unsigned char MASK_4BYTE = 0xF8;
  constexpr unsigned char MASK_3BYTE = 0xF0;
  constexpr unsigned char MASK_2BYTE = 0xE0;

  constexpr unsigned char PATTERN_4BYTE = 0xF0;
  constexpr unsigned char PATTERN_3BYTE = 0xE0;
  constexpr unsigned char PATTERN_2BYTE = 0xC0;

  constexpr int BYTE_LEN_1 = 1;
  constexpr int BYTE_LEN_2 = 2;
  constexpr int BYTE_LEN_3 = 3;
  constexpr int BYTE_LEN_4 = 4;

  inline int getCharLength(unsigned char firstByte) {
    if ((firstByte & MASK_4BYTE) == PATTERN_4BYTE) return BYTE_LEN_4;
    if ((firstByte & MASK_3BYTE) == PATTERN_3BYTE) return BYTE_LEN_3;
    if ((firstByte & MASK_2BYTE) == PATTERN_2BYTE) return BYTE_LEN_2;
    return BYTE_LEN_1;
  }
}

void fillMap(const std::string& buf, std::map<std::string, int>& wCount);

Indexer::Indexer(){}

void Indexer::index(const std::string& fileName, DataBase& db)
{
  std::ifstream inputFile(fileName, std::ios::binary);
  if (!inputFile.is_open()) {
    throw std::runtime_error("Can`t open file " + fileName);
  }

  std::string fileData((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
  inputFile.close();

  std::wstring wideData;
  wideData = String_modify::to_wstring(fileData);

  boost::locale::generator gen;
  std::locale loc = gen("ru_RU.UTF-8");

  std::wstring resultWide{};  

  for (wchar_t ch : wideData) {
    if (std::isalpha(ch, loc)) {
      resultWide += ch;
    }
    else {
      resultWide += L' ';
    }
  }
  std::string cleanedSTR = String_modify::wstring_to_utf8(resultWide);

  std::string lower = boost::locale::to_lower(cleanedSTR, loc);

  std::map<std::string, int> wordCount;
  {
    std::lock_guard<std::mutex> lock(mutex_);

    fillMap(lower, wordCount);

    int doc_id = db.addDocument(fileName);
    if (doc_id > 0)
    {
      for (const std::pair<std::string, int>& pair : wordCount)
      {
        int word_id = db.addWord(pair.first);
        if (word_id > 0)
        {
          db.addWordsDocuments(doc_id, word_id, pair.second);
        }
      }
    }
  }
}

void fillMap(const std::string& buf, std::map<std::string, int>& wCount)
{
  bool isWhitespace = false;
  std::string word;
  for (const char& ch : buf)
  {
    if (ch != WHITESPACE)
    {
      word.push_back(ch);
      isWhitespace = false;
    }
    else if (!isWhitespace)
    {
      size_t charCount = 0;
      for (size_t i = 0; i < word.size(); ) {
        unsigned char c = word[i];
        int charLen = Utf8Constants::getCharLength(c);
        i += charLen;
        charCount++;
      }
      if (charCount >= WordLength::MIN_WORD_LENGTH && charCount <= WordLength::MAX_WORD_LENGTH) {
        wCount[word]++;        
      }
      isWhitespace = true;
      word.clear();
    }
  }
  if (!word.empty())
  {
    size_t charCount = 0;
    for (size_t i = 0; i < word.size(); ) {
      unsigned char c = word[i];
      i += Utf8Constants::getCharLength(c);
      charCount++;
    }
    if (charCount >= WordLength::MIN_WORD_LENGTH && charCount <= WordLength::MAX_WORD_LENGTH) {
      wCount[word]++;
    }
  }
}

 
