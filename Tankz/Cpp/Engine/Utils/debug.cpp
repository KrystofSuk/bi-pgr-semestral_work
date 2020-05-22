#include "Engine/Utils/debug.h"


void sukkryst::Debug::Log(const std::string& s)
{
	std::cout << s << std::endl;
}

void sukkryst::Debug::Log(const Printable& comp)
{
	std::cout << comp.Print() << std::endl;
}
