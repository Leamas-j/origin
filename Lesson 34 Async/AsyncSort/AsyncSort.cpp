#include <iostream>
#include <random>
#include <vector>
#include <thread>
#include <future>

void printVector(const std::vector<int> &v)
{
	for (const auto& t : v) {
		std::cout << t << " ";
	}
	std::cout << std::endl;	
}

void findMin(const std::vector<int> &v, const int i, int &pos, std::promise<int> pr)
{
	int min = v[i];
	for (int j = i; j < v.size(); ++j)
	{	
		if (v[j] <= min)
		{
			min = v[j];
			pos = j;
		}
	}
	pr.set_value(min);
}

int main()
{
	std::random_device rd;
	std::mt19937 gen{ rd() };
	std::uniform_int_distribution<> dis(0, 100);
	
	std::vector<int> vec;

	for (int i = 0; i < 15; ++i) {
		vec.push_back( dis(gen));
	}

	printVector(vec);

	for (int i = 0; i < vec.size(); ++i)
	{		
		int pos = 0;

		std::promise<int> prom;
		std::future<int> min = prom.get_future();
		
		auto res = async(findMin, std::ref(vec), i, std::ref(pos), move(prom));
		min.wait();

		vec[pos] = vec[i];
		vec[i] = min.get();		
	}

	printVector(vec);	
}
