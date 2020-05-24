#pragma once
#include "Engine/Core/component.h"
#include "Engine/Core/scene.h"

namespace sukkryst
{

	/**
	 * @brief Day night script
	 * 
	 */
	struct DayNight : public Component
	{

		bool use = true;

		Scene &scene;

		glm::vec3 speed;
		glm::vec3 nightFogColor;

		float intensity = 1.0f;

		/**
		 * @brief Construct a new Day Night component
		 * 
		 * @param scene to modify light in
		 */
		DayNight(Scene &scene);

		/**
		 * @brief Update the cycle
		 * 
		 */
		void Update();

		/**
		 * @brief Destroy the Day Night object
		 * 
		 */
		~DayNight();
	};

} // namespace sukkryst