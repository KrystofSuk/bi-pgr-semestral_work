#include "Engine/Core/game_object.h"


GameObject::GameObject(const std::string& name) : name(name)
{
	std::hash<std::string> hasher;
	id = hasher(name);
	std::cout << name << " - " <<  (unsigned int)id << std::endl;
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

void GameObject::OnClick(const unsigned char& id)
{
	if (id == this->id) {
		for (auto& it : _components)
			it.second->OnClick();
	}
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
