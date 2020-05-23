#pragma once

#include "Engine/Core/component.h"
#include "Engine/Core/spline.h"

namespace sukkryst
{

	/**
	 * @brief Animation script
	 * 
	 */
	struct Animator : public Component
	{

		bool animating = true;
		float internalTime = 0;
		float speed = 1.0f;

		//If it modify rotation or position
		std::string param;

		Spline *track;

		/**
		 * @brief Construct a new Animator with spline and specific parameter to modify
		 * 
		 * @param track spline of animation
		 * @param param if rotation or position is modified
		 */
		Animator(Spline *track, const std::string &param);

		/**
		 * @brief Updates the animation by speed and time
		 * 
		 */
		void Update();

		/**
		 * @brief Enables disables animation
		 * 
		 */
		void OnClick();

		/**
		 * @brief Destroy the Animator object
		 * 
		 */
		~Animator();
	};

} // namespace sukkryst