#include <iostream>
#include <exception>
#include "Windows.h"

class smart_array {
public:
    smart_array(int size) {
		this->current = 0;
		this->size = size;
		data = new int[size] {0};
    }
	void add_element(int elem) {
		if (current < size) {
			data[current] = elem;
			current++;
		}
		else throw std::exception("Выход за рамки массива!");
	}
	int get_element(int elemNum) {
		if (elemNum < size) {
			return data[elemNum];
		}
		else throw std::exception("Выход за рамки массива!");
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
		arr.add_element(14);
		arr.add_element(15);
		std::cout << arr.get_element(1) << std::endl;
	}
	catch (const std::exception& ex) {
		std::cout << ex.what() << std::endl;
	}
}

