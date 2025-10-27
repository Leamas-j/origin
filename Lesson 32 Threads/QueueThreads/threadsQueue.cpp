#include <thread>
#include <chrono>
#include <iostream>

void CustomersTh(const int &maxCust, int &cust, bool &maxArriv) {

  while(cust < maxCust) {

    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "+ " << ++cust << std::endl;
  }

  maxArriv = true;
}

void OperatorTh(int &cust, bool &maxArriv) {

  while (!maxArriv || cust) {

    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "- " << --cust << std::endl;
  }
}

int main()
{
  int customers{ 0 }; 
  bool maxArrived{ false }; 
  int maxCustomers{ 10 };

  std::thread customersThread(CustomersTh, std::ref(maxCustomers), std::ref(customers), std::ref(maxArrived));
  std::thread operatorThread(OperatorTh, std::ref(customers), std::ref(maxArrived));

  customersThread.join();
  operatorThread.join();
  
  return 0;
}

