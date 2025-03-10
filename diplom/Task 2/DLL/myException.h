#pragma once

#include <iostream>
#include <string>
#include <stdexcept>

class MyException : public std::domain_error
{
	const char* msg;
public:
	const char* what() const override;
	MyException(const char* msg);
};

