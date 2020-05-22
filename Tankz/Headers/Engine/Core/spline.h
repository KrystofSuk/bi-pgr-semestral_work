#pragma once

#include <vector>
#include <pgr.h>

namespace sukkryst {

	struct Spline
	{
		std::vector<glm::vec3> points;

		Spline();
		Spline(const std::vector<glm::vec3>& points);

		glm::vec3 Evaluate(const float& t);
	};

}