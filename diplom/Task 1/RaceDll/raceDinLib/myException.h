#pragma once

#include <iostream>
#include <string>
#include <stdexcept>

#ifdef RACEDINLIB_EXPORTS
#define EXP __declspec(dllexport)
#else
#define EXP __declspec(dllimport)
#endif

class EXP MyException : public std::domain_error
{
	const char* msg;
public:
	const char* what() const override;
	MyException(const char* msg);
};

