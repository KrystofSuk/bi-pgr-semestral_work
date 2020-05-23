#pragma once
#include "Engine/Components/light.h"

namespace sukkryst
{
	/**
	 * @brief Directon light component
	 * 
	 */
	struct DirectionLight : public Light
	{
		/**
		 * @brief Construct a new Direction Light object
		 * 
		 */
		DirectionLight();

		/**
		 * @brief Processes the light and adds specific shader the data at specific index
		 * 
		 * @param shader to add light data
		 * @param index to light index in shader
		 */
		void ProcessLight(Shader *shader, const std::string &index = "");
	};

} // namespace sukkryst