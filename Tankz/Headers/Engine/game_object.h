#pragma once

#include <string>
#include <unordered_map>

#include "component.h"
#include "Components/transform.h"

class GameObject {
private:
	std::unordered_map<std::string, Component*> _components;
public:
	Transform * transform;
	std::string name;

	GameObject(const std::string & name);

	void AddComponent(Component * component);

	template <typename T>
	T* GetComponent() const;

	~GameObject();
};

template<typename T>
inline T* GameObject::GetComponent() const
{
	
	auto it = _components.begin();
	while (it != _components.end())
	{
		if (dynamic_cast<T*>(it->second) != nullptr)
			return dynamic_cast<T*>(it->second);
		it++;
	}
	
	throw ("Component not found!");
}
