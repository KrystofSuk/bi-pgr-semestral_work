#include "Engine/Core/spline.h"
#include <iostream>

sukkryst::Spline::Spline(const std::vector<glm::vec3>& points)
{
	this->points = points;
}

sukkryst::Spline::Spline()
{

}

glm::vec3 sukkryst::Spline::Evaluate(const float& tmain)
{
	int index = fmod(tmain, points.size());
	float t = fmod(tmain, points.size()) - floor(fmod(tmain, points.size()));
	glm::vec3 p1 = points[(index - 1 + points.size()) % points.size()];
	glm::vec3 p2 = points[(index) % points.size()];
	glm::vec3 p3 = points[(index + 1) % points.size()];
	glm::vec3 p4 = points[(index + 2) % points.size()];

	const float t2 = t * t;
	const float t3 = t * t2;

	glm::vec3 result =
		p1 * (-.5f * t3 + 1.0f * t2 + -.5f * t + .0f * 1.0f)
		+ p2 * (1.5f * t3 + -2.5f * t2 + .0f * t + 1.0f * 1.0f)
		+ p3 * (-1.5f * t3 + 2.0f * t2 + 0.5f * t + .0f * 1.0f)
		+ p4 * (.5f * t3 + -.5f * t2 + .0f * t + .0f * 1.0f);


	glm::vec4 tM = glm::vec4(t3, t2, t, 1);
	glm::mat4x4 mM = glm::mat4x4(
		-.5f, 1.5f, -1.5f, .5f,
		1.0f, -2.5f, 2.0f, -.5f,
		-.5f, .0f, .5f, .0f,
		.0f, 1.0f, .0f, .0f
	);
	//auto result = tM * mM;
	//std::cout << result.x << " " <<  << std::endl;


	return result;
}

