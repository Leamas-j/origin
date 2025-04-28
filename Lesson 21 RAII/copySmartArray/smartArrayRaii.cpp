#include <iostream>
#include <exception>
#include "Windows.h"

class smart_array {
public:
  smart_array(int size) {
	if (size > 0) {
	  this->current = 0;
	  this->size = size;
	  data = new int[size] {0};
	}
	else throw std::exception("Недопустимый размер массива!");
  }
void add_element(int elem) {
  if (current < size) {
    data[current] = elem;
	current++;
  }
  else throw std::exception("Выход за рамки массива!");
}
int get_element(int elemNum) {
  if ((elemNum < size) && (elemNum >= 0)) {
    return data[elemNum];
  }
  else throw std::exception("Выход за рамки массива!");
}
smart_array& operator =(const smart_array& other) {
  if (this != &other) {
	delete[] this->data;
	this->size = other.size;
	this->current = other.current;
	this->data = new int[size];
	for (int i = 0; i < size; ++i) {
	  this->data[i] = other.data[i];
	}
  }
  return *this;
}
~smart_array() {
  delete[] data;
}
private:
  int current;
  int size;
  int* data{ nullptr };
};

int main()
{
  SetConsoleOutputCP(1251);
  try {
	smart_array arr(5);
	arr.add_element(1);
	arr.add_element(4);
	arr.add_element(155);

	smart_array new_array(2);
	new_array.add_element(44);
	new_array.add_element(34);
	
	arr = new_array;		
  }
  catch (const std::exception& ex) {
	std::cout << ex.what() << std::endl;
  }
}

