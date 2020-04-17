#pragma once

#include "./light.h"

struct SpotLight : public Light {
	void ProcessLight(Shader* shader, const std::string& index = "");
};