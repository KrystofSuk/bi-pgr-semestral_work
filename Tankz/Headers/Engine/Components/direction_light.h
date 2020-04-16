#pragma once
#include "./light.h"

struct DirectionLight : public Light {
	void ProcessLight(Shader* shader);
};