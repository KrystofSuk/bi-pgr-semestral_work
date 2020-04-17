#pragma once
#include "Engine/Components/light.h"

struct PointLight : public Light {
	void ProcessLight(Shader* shader, const std::string& index = "");
};
