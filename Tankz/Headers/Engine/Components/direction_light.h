#pragma once
#include "Engine/Components/light.h"

struct DirectionLight : public Light {
	void ProcessLight(Shader* shader, const std::string& index = "");
};