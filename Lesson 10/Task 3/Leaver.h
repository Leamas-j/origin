#pragma once
#include <iostream>

class  Leaver {
	std::string name;
public:
	Leaver(std::string name);
	std::string leave();
};