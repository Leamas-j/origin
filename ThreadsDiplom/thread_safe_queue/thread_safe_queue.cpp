#include <iostream>
#include <functional>
#include <queue>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <atomic>

using namespace std;

template <typename T>
class safe_queue
{
private:
  queue<T> queue_;
  mutable mutex mutex_;
  condition_variable cond_var_;
  atomic<bool> stop_flag_;

public:
  safe_queue() : stop_flag_(false) {};

  void push(T item)
  {
    unique_lock<mutex> lock(mutex_);
    queue_.push(move(item));
    lock.unlock();

    cond_var_.notify_one();
  }

  bool pop(T& item)
  {
    unique_lock<mutex> lock(mutex_);
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
    lock_guard<mutex> lock(mutex_);
    return queue_.empty();
  }
};

class thread_pool
{
private:
  vector<thread> workers_;
  safe_queue<function<void()>> tasks_;
  atomic<bool> stop_flag_{ false };
  atomic<int> active_tasks_{ 0 };

public:
  explicit thread_pool(size_t num_threads)
  {
    for (size_t i = 0; i < num_threads; ++i)
    {
      workers_.push_back(thread(&thread_pool::work, this));
    }
  }

  ~thread_pool()
  {
    stop_flag_ = true;
    tasks_.stop_worker();
    for (auto& w : workers_)
    {
      w.join();
    }
    cout << "End" << endl;
  }

  void work()
  {
    while (!stop_flag_)
    {
      function<void()> task;
      if (tasks_.pop(task))
      {
        task();
      }
    }
  }

  void submit(function<void()> task)
  {
    if (!stop_flag_)
    {
      tasks_.push(task);
    }
  }

  void stop()
  {
    stop_flag_ = true;
    tasks_.stop_worker();
  }

  bool empty_safe_queue()
  {
    return tasks_.empty_queue();
  }
};

mutex m;

void F1()
{
  this_thread::sleep_for(chrono::seconds(1));
  lock_guard<mutex> lock(m);
  cout << " F1 id: " << this_thread::get_id() << endl;
}

void F2()
{
  this_thread::sleep_for(chrono::seconds(1));
  lock_guard<mutex> lock(m);
  cout << " F2 id: " << this_thread::get_id() << endl;
}

int main()
{
  int num_threads = thread::hardware_concurrency() - 1;

  cout << "Count of threads: " << num_threads << endl;

  thread_pool pool(num_threads);

  for (int i = 0; i < 10; ++i)
  {
    pool.submit(F1);
    pool.submit(F2);
    this_thread::sleep_for(chrono::seconds(1));
  }

  while (!pool.empty_safe_queue())
  {
    this_thread::sleep_for(chrono::milliseconds(100));
  }

  return 0;
}
