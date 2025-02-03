#pragma once
#include <exception>

class MyException : public std::exception{
public:
	MyException(const char* msg);
	const char* what() const override;
private:
	const char* msg;
};

