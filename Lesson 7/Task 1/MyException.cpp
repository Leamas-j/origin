#include "MyException.h"

MyException::MyException(const char* msg) : std::exception(msg){
	this->msg = msg;
}

const char* MyException::what() const
{
	return msg;
}
