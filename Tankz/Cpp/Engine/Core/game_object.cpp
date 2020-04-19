#include "Engine/Core/game_object.h"


GameObject::GameObject(const std::string& name) : name(name)
{
	transform = new Transform();
}

void GameObject::Update()
{
	auto it = _components.begin();
	while (it != _components.end())
	{
		it->second->Update();
		it++;
	}
}

void GameObject::AddComponent(Component* component)
{
	component->gameObject = this;
	component->transform = transform;

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
