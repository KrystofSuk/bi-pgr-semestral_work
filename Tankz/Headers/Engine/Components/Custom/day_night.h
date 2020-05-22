#pragma once
#include "Engine/Core/component.h"
#include "Engine/Core/scene.h"

namespace sukkryst {

	struct DayNight : public Component {

		bool use = true;

		Scene& scene;
		glm::vec3 speed;
		glm::vec3 nightFogColor;
		float intensity = 1.0f;

		DayNight(Scene& scene);

		void Update();

		std::string Print() const;

		friend std::ostream& operator<<(std::ostream& out, const DayNight& component);

		~DayNight();
	};

}