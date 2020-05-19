#pragma once

#include <string>
#include <unordered_map>
#include <functional>

#include "Engine/Core/component.h"
#include "Engine/Core/transform.h"

class GameObject {
private:
	std::unordered_map<std::string, Component*> _components;
public:
	Transform * transform;
	std::string name;
	unsigned char id;

	GameObject(const std::string & name);

	void Update();

	void AddComponent(Component * component);

	void OnClick(const unsigned char& id);

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
