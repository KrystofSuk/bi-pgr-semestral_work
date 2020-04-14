#pragma once

#include <string>
#include "shader.h"

class Material {
public:
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

	Material(const std::string& name, Shader * shader);
	~Material();
};