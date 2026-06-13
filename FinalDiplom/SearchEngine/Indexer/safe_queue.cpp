#include <iostream>
#include <functional>
#include <queue>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>

template <typename T>
class safe_queue
{
private:
  std::queue<T> queue_;
  mutable std::mutex mutex_;
  std::condition_variable cond_var_;
  std::atomic<bool> stop_flag_;

public:
  safe_queue() : stop_flag_(false) {};

  void push(T item)
  {
    std::unique_lock<std::mutex> lock(mutex_);
    queue_.push(item);
    lock.unlock();

    cond_var_.notify_one();
  }

  bool pop(T& item)
  {
    std::unique_lock<std::mutex> lock(mutex_);
    cond_var_.wait(lock, [this]()
      {
        return !queue_.empty() || stop_flag_;
      });

    if (stop_flag_ && queue_.empty())
    {
      return false;
    }

    item = queue_.front();
    queue_.pop();
    return true;
  }

  void stop_worker()
  {
    stop_flag_ = true;
    cond_var_.notify_all();
  }

  bool empty_queue()
  {
    std::lock_guard<std::mutex> lock(mutex_);
    return queue_.empty();
  }
};
