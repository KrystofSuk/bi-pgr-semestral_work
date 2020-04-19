#pragma once
#include "Engine/Components/light.h"

struct PointLight : public Light {
	PointLight();
	void ProcessLight(Shader* shader, const std::string& index = "");
};
