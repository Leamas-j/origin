#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <map>
#include <stdexcept>
#include <mutex>

#include "database.h"

class Indexer
{
private:  
  std::mutex mutex_;

public:
  Indexer();
  void index(const std::string& fileName, DataBase& db);
};

