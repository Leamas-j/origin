#include <iostream>
#include <exception>
#include <vector>

template<typename T>
class myVector {
  int m_size;
  int m_capacity;
  int m_end;
  T* arr;
public:
  myVector(int size_) {
    if (size_ <= 0)  throw std::exception("Ошибка размера массива!");
    m_size = size_;
    m_capacity = size_;
    arr = new T[m_size]; 
    m_end = 0;
  }
  T at(int index) {
    if(index >= m_size)  throw std::exception("Выход за рамки массива!");
    return arr[index];
  }
  void push_back(T value) {
    if (m_end < m_size) {
      arr[m_end] = value;
      m_end++;
    }
    else if (m_capacity == m_size) {
      m_capacity *= 2;
      T* newArr = new T[m_capacity];
      for (int i = 0; i < m_size; ++i) {
        newArr[i] = arr[i];
      }
      newArr[m_size] = value;
      m_size++;
      m_end++;
      delete[]arr;
      arr = newArr;     
    }
    else {
      arr[m_size] = value;
      m_size++;
      m_end++;
    }    
  }
  int size() {
    return m_size;
  }
  int capacity() {
    return m_capacity;
  }
 
  ~myVector(){
    delete[] arr;
  }
};

int main()
{
  myVector<int> vec(2);
  vec.push_back(2);
  vec.push_back(4);
  vec.push_back(6);
  vec.push_back(8);
  vec.push_back(10);
  for (int i = 0; i < vec.size(); ++i) {
    std::cout << vec.at(i) << " ";
  } 
  std::cout << std::endl;
  std::cout << vec.size() << " " << vec.capacity();  
}
