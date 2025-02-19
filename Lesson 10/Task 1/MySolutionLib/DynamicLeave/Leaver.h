#pragma once
#include <iostream>

class Leaver {
	std::string name;
public:
	__declspec(dllexport) Leaver(std::string name);
	std::string __declspec(dllexport) leave();
};
