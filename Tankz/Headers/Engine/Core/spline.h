#pragma once

#include <vector>
#include <pgr.h>

namespace sukkryst {

	/**
	 * @brief Spline struct for catmull-rom 
	 * 
	 */
	struct Spline
	{
		std::vector<glm::vec3> points;

		/**
		 * @brief Construct a new Spline object
		 * 
		 */
		Spline();

		/**
		 * @brief Construct a new Spline object with defined points
		 * 
		 * @param points of the curve
		 */
		Spline(const std::vector<glm::vec3>& points);

		/**
		 * @brief Evaluates the animation in desired time
		 * 
		 * @param t desired time of animation
		 * @return glm::vec3 result of catmull-rom
		 */
		glm::vec3 Evaluate(const float& t);
	};

}