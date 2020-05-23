#pragma once

#include <string>
#include <unordered_map>
#include <functional>

#include "Engine/Core/component.h"
#include "Engine/Core/transform.h"

namespace sukkryst
{

	/**
	 * @brief Basic gameobject engine representation with update and on click methods + its containing components + transform
	 * 
	 */
	class GameObject
	{
	private:
		std::unordered_map<std::string, Component *> _components;

	public:
		Transform *transform;
		std::string name;
		unsigned char id;

		/**
		 * @brief Construct a new gameobject with specific name
		 * 
		 * @param name of gameobject
		 */
		GameObject(const std::string &name);

		/**
		 * @brief Calls update in every component
		 * 
		 */
		void Update();

		/**
		 * @brief Adds new component to gameobject
		 * 
		 * @param component to add
		 */
		void AddComponent(Component *component);

		/**
		 * @brief Distribute click call to gameobject components if id mathes gameobject's id
		 * 
		 * @param char specific id of gameobject
		 */
		void OnClick(const unsigned char &id);

		/**
		 * @brief Get the Component casted to its type searched by desired type
		 * 
		 * @tparam T component type
		 * @return T* founded component
		 */
		template <typename T>
		T *GetComponent() const;

		/**
		 * @brief Destroy the gameobject
		 * 
		 */
		~GameObject();
	};

	template <typename T>
	inline T *GameObject::GetComponent() const
	{

		auto it = _components.begin();
		while (it != _components.end())
		{
			if (dynamic_cast<T *>(it->second) != nullptr)
				return dynamic_cast<T *>(it->second);
			it++;
		}

		throw("Component not found!");
	}

} // namespace sukkryst
