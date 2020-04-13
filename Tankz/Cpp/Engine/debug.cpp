#include "..\..\Headers\Engine\debug.h"

void Debug::Log(const std::string& s)
{
	std::cout << s << std::endl;
}

void Debug::Log(const Printable& comp)
{
	std::cout << comp.Print() << std::endl;
}
