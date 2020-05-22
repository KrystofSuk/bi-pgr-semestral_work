#include "Engine/Core/component.h"


sukkryst::Component::Component() : name("Unnamed")
{
}

sukkryst::Component::Component(std::string name) : name(name)
{
}

void sukkryst::Component::OnClick()
{
}

void sukkryst::Component::Update()
{
}

sukkryst::Component::~Component()
{
}

std::ostream& operator<<(std::ostream& out, const sukkryst::Component& c)
{
	return out << c.Print() << std::endl;
}
