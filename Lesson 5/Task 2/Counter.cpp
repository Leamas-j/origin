#include "Counter.h"

Counter::Counter(int num) { this->num = num; }
Counter::Counter() { num = 1; }
void Counter::incr() { ++num; }
void Counter::decr() { --num; }
int Counter::current() { return num; }

