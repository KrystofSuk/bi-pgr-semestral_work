#pragma once
#include <string>
#include <iostream>

#include "Engine/Core/component.h"
#include "Engine/Utils/printable.h"

struct Debug {
	static void Log(const std::string& s);
	static void Log(const Printable& comp);
};