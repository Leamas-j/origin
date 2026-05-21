#pragma once

#include "safe_queue.cpp"
#include "indexer.h"
#include "database.h"

class Thread_pool
{
private:
    std::vector<std::thread> workers_;
    safe_queue<std::string> files_;
    std::atomic<bool> stop_flag_;
    DataBase& dbase_;

public:
    Thread_pool(const int& num_threads, DataBase& db);
    ~Thread_pool();
    void work();
    void submit(const std::string& file);
    void stop();
    bool empty_safe_queue(); 
};

