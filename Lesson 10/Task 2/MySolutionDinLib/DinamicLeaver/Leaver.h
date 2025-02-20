#pragma once
#include <iostream>
#ifdef DINAMICLEAVER_EXPORTS
#define EXP __declspec(dllexport)
#else
#define EXP __declspec(dllimport)
#endif

class EXP Leaver {
	std::string name;
public:
	Leaver(std::string name);
	std::string leave();
};