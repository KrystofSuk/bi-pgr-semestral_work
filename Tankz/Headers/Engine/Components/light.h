#pragma once
#include <string>

#include "pgr.h"
#include "Engine/Core/component.h"
#include "Engine/Core/shader.h"

namespace sukkryst
{

	/**
	 * @brief Light component
	 * 
	 */
	struct Light : public Component
	{
		// 0 = direction, 1 = point, 2 = spot
		unsigned type = 0;

		bool on = true;

		glm::vec3 diffuse;
		glm::vec3 ambient;
		glm::vec3 specular;

		float intensity;
		float shininess;

		/**
		 * @brief Construct a new Light object
		 * 
		 */
		Light();

		/**
		 * @brief On click on off
		 * 
		 */
		void OnClick();
		
		/**
		 * @brief Processes the light and adds specific shader the data at specific index
		 * 
		 * @param shader to add light data
		 * @param index to light index in shader
		 */
		virtual void ProcessLight(Shader *shader, const std::string &index = "") = 0;

		/**
		 * @brief Destroy the Light object
		 * 
		 */
		virtual ~Light();
	};

} // namespace sukkryst