#include "thread_pool.h"

std::mutex cout_mutex;

Thread_pool :: Thread_pool(const int& num_threads, DataBase& db) : dbase_(db), stop_flag_(false)
{
  for(int i = 0; i < num_threads; ++i)
  {
    workers_.push_back(std::thread(&Thread_pool::work, this));
  }
}

Thread_pool :: ~Thread_pool()
{
  stop_flag_ = true;
  files_.stop_worker();
  for (auto& w : workers_)
  {
    if (w.joinable())
    {
      w.join();
    }
  }
}

void Thread_pool::work()
{
  while (!stop_flag_)
  {
    std::string file;
    if (files_.pop(file))
    {      
      try { 
        if (file.size())
        {
          {
            std::lock_guard<std::mutex> lock(cout_mutex);
            std::cout << file << std::endl;
          }
          Indexer indexer;
          indexer.index(file, dbase_);         
        }              
      }
      catch (const std::exception& e)
      {
        std::cout << e.what();
      }     
    }
  }
}

void Thread_pool :: submit(const std::string& file)
{ 
  if (!stop_flag_)
  {    
    files_.push(file);
  }
}

void Thread_pool :: stop()
{
  stop_flag_ = true;
  files_.stop_worker();
}

bool Thread_pool :: empty_safe_queue()
{
  return files_.empty_queue();
}
