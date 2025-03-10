#include "air.h"
#include "myException.h"

void Air::calcRaceResult() {
	if (!speed) throw MyException("Division by zero");
	result = distance * calcDecrease() / speed;
}