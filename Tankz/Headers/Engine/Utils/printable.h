#pragma once

#include <string>

namespace sukkryst {

	struct Printable {
		virtual std::string Print() const { return ""; };
	};

}