#pragma once

#include <string>

#include "Engine/Core/shader.h"

namespace sukkryst {

	/**
	 * @brief Material representation
	 * 
	 */
	struct Material {
		std::string name;

		Shader* shader;

		glm::vec3 diffuse;
		glm::vec3 specular;
		glm::vec3 emission;

		float shininess;

		bool diffuseMap;

		/**
		 * @brief Construct a new Material
		 * 
		 * @param name of material
		 * @param shader used shader
		 */
		Material(const std::string& name, Shader* shader);

		/**
		 * @brief Destroy the Material object
		 * 
		 */
		~Material();
	};

}