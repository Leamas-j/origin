#include <iostream>
#include <mutex> 

class Data {
private:
  int value_;
  std::mutex mtx_;

public:
  Data(int value) : value_(value) {}

  int getValue() {
    return value_;
  }

  void setValue(int newVal) {
    value_ = newVal;
  }

  std::mutex& getMutex() {
    return mtx_;
  }
};

void swapData(Data& a, Data& b)
{
  int tmp = a.getValue();
  a.setValue(b.getValue());
  b.setValue(tmp);
}

void swap_lock(Data &a, Data &b) 
{  
  std::lock(a.getMutex(), b.getMutex());
  std::lock_guard<std::mutex> lk1(a.getMutex(), std::adopt_lock);
  std::lock_guard<std::mutex> lk2(b.getMutex(), std::adopt_lock);

  swapData(a, b);
}

void swap_scoped_lock(Data& a, Data& b)
{
  std::scoped_lock lk(a.getMutex(), b.getMutex());

  swapData(a, b);
}

void swap_unique_lock(Data& a, Data& b)
{  
  std::unique_lock<std::mutex> lk1(a.getMutex(), std::defer_lock);
  std::unique_lock<std::mutex> lk2(b.getMutex(), std::defer_lock); 
  std::lock(lk1, lk2);  
 
  swapData(a, b);
}


int main()
{
  Data d1(3), d2(9);

  std::cout << "Data before swap: " << d1.getValue() << " " << d2.getValue() << std::endl;

  swap_lock(d1, d2);
  std::cout <<  "Swap using Lock: " << d1.getValue() << " " << d2.getValue() << std::endl;

  swap_unique_lock(d1, d2);
  std::cout << "Swap using unique_lock: " << d1.getValue() << " " << d2.getValue() << std::endl;

  swap_scoped_lock(d1, d2);
  std::cout << "Swap using scoped_lock: " << d1.getValue() << " " << d2.getValue() << std::endl;

  return 0;
}
