#include "..\..\Headers\Engine\component.h"

Component::Component() : _name("Unnamed")
{
}

Component::Component(std::string name) : _name(name)
{
}

Component::~Component()
{
}

std::ostream& operator<<(std::ostream& out, const Component& c)
{
	return out << c.Print() << std::endl;
}
