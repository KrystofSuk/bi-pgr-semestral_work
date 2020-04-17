#pragma once

#include <string>

struct Printable {
	virtual std::string Print() const { return ""; };
};