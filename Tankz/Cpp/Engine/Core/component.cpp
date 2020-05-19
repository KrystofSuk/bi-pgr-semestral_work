#include "Engine/Core/component.h"


Component::Component() : name("Unnamed")
{
}

Component::Component(std::string name) : name(name)
{
}

void Component::OnClick()
{
}

void Component::Update()
{
}

Component::~Component()
{
}

std::ostream& operator<<(std::ostream& out, const Component& c)
{
	return out << c.Print() << std::endl;
}
