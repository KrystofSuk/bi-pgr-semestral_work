#include "Engine/Core/material.h"


Material::Material(const std::string& name, Shader* shader) : name(name), shader(shader)
{
	diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
	emission = glm::vec3(0.0f, 0.0f, 0.0f);
	specular = glm::vec3(1.0f, 1.0f, 1.0f);
	shininess = 0.5f;

	diffuseMap = false;
}

Material::~Material()
{
}
