#pragma once
#include <string>
#include <iostream>
#include "component.h"
#include "printable.h"

struct Debug {
	static void Log(const std::string& s);
	static void Log(const Printable& comp);
};