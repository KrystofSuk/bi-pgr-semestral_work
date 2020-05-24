#pragma once
#include <string>
#include <iostream>

#include "Engine/Core/transform.h"

namespace sukkryst
{

	/**
	 * @brief Basic component with update and click methods
	 * 
	 */
	class Component
	{
	public:
		//Pointer to parent gameobject but need to be casted to GameObject
		void *gameObject;
		Transform *transform;
		std::string name;

		/**
		 * @brief Construct a new Component object
		 * 
		 */
		Component();

		/**
		 * @brief Construct a new Component object with specified name
		 * 
		 * @param name of component
		 */
		Component(std::string name);

		/**
		 * @brief OnCLick overritable method
		 * 
		 */
		virtual void OnClick();

		/**
		 * @brief Update overritable method called every timer tick
		 * 
		 */
		virtual void Update();

		/**
		 * @brief Destroy the Component object
		 * 
		 */
		virtual ~Component();
	};

} // namespace sukkryst