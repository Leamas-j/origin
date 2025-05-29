#include <iostream>

template <typename T>
class myUniquePtr {
public:
 
  myUniquePtr(T* ptr) : ptr_(ptr) {}
  
  T& operator*() const {
    if (!ptr_) {
      throw std::runtime_error("Попытка разыменования пустого указателя!");
    }
    return *ptr_;
  }

  T* operator->() const {
    if (!ptr_) {
      throw std::runtime_error("Попытка доступа к пустому указателю!");
    }
    return ptr_;
  }

  myUniquePtr& operator=(const myUniquePtr&) = delete;
 
  myUniquePtr(const myUniquePtr&) = delete;

  T* release() {
    T* ptr = ptr_;
    ptr_ = nullptr;
    return ptr;
  } 

  ~myUniquePtr() {
    delete ptr_;
  }

private:
  T* ptr_;
};

int main() {
  myUniquePtr<int> p(new int(8));

  std::cout << *p << std::endl;  

  int* s_ptr = p.release(); 

  std::cout << *s_ptr << std::endl; 

  delete s_ptr; 

  return 0;
}