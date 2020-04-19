#pragma once

#include "Engine/Components/light.h"

struct SpotLight : public Light {
	SpotLight();
	void ProcessLight(Shader* shader, const std::string& index = "");
};