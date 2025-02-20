#include "Leaver.h"

Leaver::Leaver(std::string name)
{
	this->name = name;
}

std::string Leaver::leave()
{
	return std::string("До свидания, " + name + "!");
}
