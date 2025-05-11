#include <iostream>

template <class T> 
class table {
private:
	unsigned m_row;		
	unsigned m_col;			
	T **arr;				
	
public:
	table(unsigned row, unsigned col){
		m_row = row;
		m_col = col;
		arr = new T* [m_row];
		for (unsigned i = 0; i < m_row; i++) {
			arr[i] = new T[m_col];
		}
	}

	const unsigned Size() {
		return m_row * m_col * sizeof(T);
	}

	~table() {
		for (unsigned i = 0; i < m_row; i++) {
			delete[]arr[i];
		}
		delete[]arr;
	}
	const T* operator[](const int i) const {
		return arr[i];
	}
	T* operator[](const int i) {
		return arr[i];
	}	
};
 
int main() {
	auto test = table<int>(2, 3);
	test[0][0] = 4;
	std::cout << test[0][0];
}
