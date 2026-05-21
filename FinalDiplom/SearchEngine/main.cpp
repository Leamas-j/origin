#include "indexer.h"
#include "ini.h"
#include "dirReader.h"
#include "thread_pool.h"
#include "database.h"

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
    Ini ini("ini.txt");

    std::string conn_str = "host = " + ini.get_bd_host() +
      " port = " + ini.get_bd_port() +
      " dbname = " + ini.get_bd_name() +
      " user = " + ini.get_bd_user_name() +
      " password = " + ini.get_bd_user_password();

    DataBase db(conn_str);

    int num_threads = std::thread::hardware_concurrency() - 1;

    std::string startDir = ini.get_startDir();
    std::string extensions = ini.get_extensions();

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
