#include "MyException.h"

MyException::MyException(const char* msg) : std::domain_error(msg){
	this->msg = msg;
}

const char* MyException::what() const{	
	return msg;
}