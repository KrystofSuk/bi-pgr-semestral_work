#pragma once
#include <string>

#include "pgr.h"
#include "Engine/Core/component.h"
#include "Engine/Core/shader.h"

struct Light : public Component {
	glm::vec3 diffuse;
	glm::vec3 ambient;
	glm::vec3 specular;

	float intensity;
	float shininess;
		
	Light();

	virtual void ProcessLight(Shader* shader, const std::string& index = "") = 0;

	virtual std::string Print() const;
	friend std::ostream& operator<<(std::ostream& out, const Light& light);
	virtual ~Light();
};