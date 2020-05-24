#pragma once

#include "Engine/Core/component.h"
#include "Engine/Core/spline.h"

namespace sukkryst
{

	/**
	 * @brief Collision box script for camera collision control
	 * 
	 */
	struct CollisionBox : public Component
	{

		glm::vec3 size;
		float yMin;

		/**
		 * @brief Construct a new Collision Box object
		 * 
		 * @param box dimensions
		 */
		CollisionBox(const glm::vec3 &box);

		/**
		 * @brief Modify the transform to fit into the box
		 * 
		 */
		void Update();

		/**
		 * @brief Destroy the Collision Box object
		 * 
		 */
		~CollisionBox();
	};

} // namespace sukkryst