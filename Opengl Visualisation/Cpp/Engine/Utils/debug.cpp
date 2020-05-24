#include "Engine/Utils/debug.h"

void sukkryst::Debug::Log(const std::string &string)
{
	std::cout << string << std::endl;
}

void sukkryst::Debug::Log(const Printable &printable)
{
	std::cout << printable.Print() << std::endl;
}
