#pragma once
#include "pgr.h"

namespace sukkryst {

	/**
	 * @brief Scene lightning representation, holds lights and fog information
	 * 
	 */
	struct LightData {
		std::vector<Light*> lights;

		glm::vec3 fogDefaultColor;
		glm::vec3 fogColor;
		
		float fogIntensity;
		float fogRamp;
		float fogHeightIntensity;
		float fogHeightRamp;
		float fogAmount = 1.0f;
		float dirAmount = 1.0f;
	};

}