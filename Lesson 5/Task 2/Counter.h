#pragma once

class Counter {
	int num;
public:
	Counter(int num);
	Counter();
	void incr();
	void decr();
	int current();
};
