#include "indexer.h"
#include "../Shared/ini_parser.h"
#include "../Shared/database.h"
#include "dirReader.h"
#include "thread_pool.h"

#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <locale.h>
#include "Windows.h"

int main()
{
  setlocale(LC_ALL, "ru_RU.UTF-8");

  try
  {
    ini_parser parser("config.ini");

    std::string conn_str = "host = " + parser.get_value("DataBase", "host") +
      " port = " + parser.get_value("DataBase", "port") +
      " dbname = " + parser.get_value("DataBase", "dbname") +
      " user = " + parser.get_value("DataBase", "user") +
      " password = " + parser.get_value("DataBase", "password");

   
    DataBase db(conn_str);

    int num_threads = std::thread::hardware_concurrency() - 1;

    std::string startDir = parser.get_value("Files", "startDir");
    std::string extensions = parser.get_value("Files", "extensions");

    DirReader dReader(extensions, startDir);

    std::vector<std::string> files = dReader.get_files(); 

    std::cout << "Indexing..." << std::endl;

    Thread_pool pool(num_threads, db);
    for(const std::string& f : files)
    {      
      pool.submit(f);                 
    }    
         
    while (!pool.empty_safe_queue())
    { 
      std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }    
    pool.stop(); 

    std::cout << "Indexing is complete!" << std::endl;
  }
  catch (const std::exception& e)
  {
    std::cout << e.what();
    return EXIT_FAILURE;
  }   
  return 0;
}
