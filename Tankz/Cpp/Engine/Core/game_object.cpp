#include "Engine/Core/game_object.h"


sukkryst::GameObject::GameObject(const std::string& name) : name(name)
{
	std::hash<std::string> hasher;
	id = hasher(name);
	std::cout << name << " - " <<  (unsigned int)id << std::endl;
	transform = new Transform();
}

void sukkryst::GameObject::Update()
{
	auto it = _components.begin();
	while (it != _components.end())
	{
		it->second->Update();
		it++;
	}
}

void sukkryst::GameObject::AddComponent(Component* component)
{
	component->gameObject = this;
	component->transform = transform;

	_components[component->name] = component;
}

void sukkryst::GameObject::OnClick(const unsigned char& id)
{
	if (id == this->id) {
		for (auto& it : _components)
			it.second->OnClick();
	}
}

sukkryst::GameObject::~GameObject()
{
	auto it = _components.begin();
	while (it != _components.end())
	{
		delete it->second;
		it++;
	}
}
