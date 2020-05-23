#pragma once
#include <string>
#include <iostream>

#include "Engine/Utils/printable.h"
#include "Engine/Core/transform.h"

namespace sukkryst {

	/**
	 * @brief Basic component with update and click methods
	 * 
	 */
	class Component : public Printable
	{
	public:
		//Pointer to parent gameobject but need to be casted to GameObject
		void* gameObject;
		Transform* transform;
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
		 * @brief Abstract method for printing the component
		 * 
		 * @return std::string representation of component
		 */
		virtual std::string Print() const = 0;

		/**
		 * @brief Method to call print when component is used in << stream
		 * 
		 * @param out output stream
		 * @param c specific component
		 * @return std::ostream& output stream
		 */
		friend std::ostream& operator<<(std::ostream& out, const Component& c);

		/**
		 * @brief Destroy the Component object
		 * 
		 */
		virtual ~Component();
	};

}