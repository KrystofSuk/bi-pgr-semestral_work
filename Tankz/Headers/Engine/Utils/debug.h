#pragma once
#include <string>
#include <iostream>

#include "Engine/Core/component.h"
#include "Engine/Utils/printable.h"

namespace sukkryst {

	struct Debug {
		static void Log(const std::string& s);
		static void Log(const Printable& comp);
	};

}