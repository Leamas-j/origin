#pragma once

#include <fstream>
#include <stdexcept>
#include <iostream>
#include <map>
#include <mutex>
#include <vector>
#include <memory>
#include <pqxx\pqxx>

class DataBase
{
  std::unique_ptr <pqxx::connection> conn_;
  std::mutex mutex_;

public:
  DataBase(const std::string& strConnect);
  void createDatabaseStructure();
  ~DataBase();
  int addWord(const std::string& word);
  int addDocument(const std::string& document);
  void addWordsDocuments(const int& document_id, const int& word_id, const int& words_count);
};

