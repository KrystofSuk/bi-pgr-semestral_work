#pragma once

#include <string>
#include "shader.h"

struct Material {
	std::string name;

	Shader* shader;

	//Properties
	//Colors
	glm::vec3 diffuse;
	glm::vec3 specular;
	glm::vec3 emission;

	//Maps
	bool diffuseMap;

	float specularAmount;

	bool useDirectionLight;

	Material(const std::string& name, Shader * shader);
	~Material();
};