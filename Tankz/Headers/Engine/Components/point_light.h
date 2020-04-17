#pragma once
#include "./light.h"

struct PointLight : public Light {
	void ProcessLight(Shader* shader, const std::string& index = "");
};
