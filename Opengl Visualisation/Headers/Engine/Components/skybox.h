#pragma once

#include <filesystem>

#include "pgr.h"
#include "Engine/Core/component.h"
#include "Engine/Core/shader.h"
#include "Engine/Core/transform.h"

namespace sukkryst
{

	/**
	 * @brief Skybox component 
	 * 
	 */
	class Skybox : public Component
	{
	public:
		GLuint vao, vbo, ebo;
		GLuint texture;
		Shader *shader;
		unsigned int faces, vert;

		/**
		 * @brief Construct a new Skybox
		 * 
		 * @param filePath to textures of the skybox
		 * @param shader of skybox
		 */
		Skybox(const std::string filePath, Shader *shader);

		/**
		 * @brief Draws skybox cube with p,v and camera matricies without depth buffer and relative to camera
		 * 
		 * @param p matrix
		 * @param v matrix
		 * @param c matrix
		 */
		void Draw(const glm::mat4 &p, const glm::mat4 &v, Transform *c);

		/**
		 * @brief Destroy the Skybox object
		 * 
		 */
		~Skybox();
	};

} // namespace sukkryst