#include "Greeter.h"

Greeter::Greeter(std::string name)
{
	this->name = name;
}

std::string Greeter::greet()
{
	return std::string("Здравствуйте, " + name + "!");
}
