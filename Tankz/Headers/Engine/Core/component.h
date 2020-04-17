#pragma once
#include <string>
#include <iostream>

#include "Engine/Utils/printable.h"

class Component : public Printable
{
public:
	void* gameObject;
	std::string name;
	Component();
	Component(std::string name);
	virtual std::string Print() const = 0;
	friend std::ostream& operator<<(std::ostream& out, const Component& c);
	virtual ~Component();
};