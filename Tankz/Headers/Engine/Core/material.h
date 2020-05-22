#pragma once

#include <string>

#include "Engine/Core/shader.h"

namespace sukkryst {

	struct Material {
		std::string name;

		Shader* shader;

		//Properties
		//Colors
		glm::vec3 diffuse;
		glm::vec3 specular;
		glm::vec3 emission;

		//Floats
		float shininess;

		//Maps
		bool diffuseMap;

		Material(const std::string& name, Shader* shader);
		~Material();
	};

}