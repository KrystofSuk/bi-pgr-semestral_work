#pragma once
#include <string>
#include <iostream>
#include "printable.h"

class Component : public Printable
{
protected:
	std::string _name;
public:
	Component();
	Component(std::string name);
	virtual std::string Print() const = 0;
	friend std::ostream& operator<<(std::ostream& out, const Component& c);
	virtual ~Component();
};