#pragma once
#include "Engine/Components/light.h"

namespace sukkryst {

	struct DirectionLight : public Light {
		void ProcessLight(Shader* shader, const std::string& index = "");
	};

}