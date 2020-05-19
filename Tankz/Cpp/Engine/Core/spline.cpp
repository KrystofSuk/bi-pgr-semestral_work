#include "Engine/Core/spline.h"
#include <iostream>

Spline::Spline(const std::vector<glm::vec3>& points)
{
	this->points = points;
}

glm::vec3 Spline::Evaluate(const float& t)
{
	int index = fmod(t, points.size());
	float fT = fmod(t, points.size()) - floor(fmod(t, points.size()));
	glm::vec3 p1 = points[(index - 1 + points.size()) % points.size()];
	glm::vec3 p2 = points[(index) % points.size()];
	glm::vec3 p3 = points[(index + 1) % points.size()];
	glm::vec3 p4 = points[(index + 2) % points.size()];
	//std::cout << index << " " << p1.x << " " << p2.x << " " << p3.x << " " << p4.x << std::endl;

	const float t2 = fT * fT;
	const float t3 = fT * t2;

	glm::vec3 result = p1 * (-t3 + 2.0f * t2 - fT)
		+ p2 * (3.0f * t3 - 5.0f * t2 + 2.0f)
		+ p3 * (-3.0f * t3 + 4.0f * t2 + fT)
		+ p4 * (t3 - t2);

	result *= 0.5f;

	return result;
}
