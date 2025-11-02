#include <thread>
#include <chrono>
#include <iostream>

void CustomersTh(const int &maxCust, std::atomic<int>&cust, bool &maxArriv) {

  while(cust < maxCust) {

    std::this_thread::sleep_for(std::chrono::seconds(1));
    cust.fetch_add(1, std::memory_order_release);
    std::cout << "+ " << cust << std::endl;
  }

  maxArriv = true;
}

void OperatorTh(std::atomic<int>&cust, bool &maxArriv) {

  while (!maxArriv || cust.load(std::memory_order_acquire)) {

    std::this_thread::sleep_for(std::chrono::seconds(2));
    cust.fetch_sub(1, std::memory_order_release);
    std::cout << "- " << cust << std::endl;
  }
}

int main()
{
  std::atomic<int> customers(0);
  bool maxArrived{ false }; 
  int maxCustomers{ 5 };

  std::thread customersThread(CustomersTh, std::ref(maxCustomers), std::ref(customers), std::ref(maxArrived));
  std::thread operatorThread(OperatorTh, std::ref(customers), std::ref(maxArrived));

  customersThread.join();
  operatorThread.join();
  
  return 0;
}

