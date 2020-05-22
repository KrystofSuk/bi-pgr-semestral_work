#pragma once
#include <string>
#include <iostream>

#include "Engine/Utils/printable.h"
#include "Engine/Core/transform.h"

namespace sukkryst {

	class Component : public Printable
	{
	public:
		void* gameObject;
		Transform* transform;
		std::string name;
		Component();
		Component(std::string name);
		virtual void OnClick();
		virtual void Update();
		virtual std::string Print() const = 0;
		friend std::ostream& operator<<(std::ostream& out, const Component& c);
		virtual ~Component();
	};

}