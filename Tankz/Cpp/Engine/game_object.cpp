#include "..\..\Headers\Engine\game_object.h"

GameObject::GameObject(const std::string& name) : name(name)
{
	transform = new Transform();
	AddComponent(transform);
}

void GameObject::AddComponent(Component* component)
{
	component->gameObject = this;
	_components[component->name] = component;
}

GameObject::~GameObject()
{
	auto it = _components.begin();
	while (it != _components.end())
	{
		delete it->second;
		it++;
	}
}
