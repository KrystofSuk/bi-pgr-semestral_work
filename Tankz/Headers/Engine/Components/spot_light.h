#pragma once

#include "Engine/Components/light.h"

struct SpotLight : public Light {
	void ProcessLight(Shader* shader, const std::string& index = "");
};