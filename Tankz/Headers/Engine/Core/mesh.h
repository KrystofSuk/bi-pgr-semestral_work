#pragma once

#include <pgr.h>
#include <iostream>

#include "Engine/Core/shader.h"

namespace sukkryst
{

	/**
	 * @brief Mesh class representation with its contetns
	 * 
	 */
	struct Mesh
	{
		GLuint vao, vbo, ebo;
		GLuint texture;
		unsigned int faces, vert;

		/**
		 * @brief Construct a new Mesh object
		 * 
		 * @param fileName path to .obj
		 * @param shader used shader to bind
		 */
		Mesh(const std::string &fileName, Shader *shader);
	};

} // namespace sukkryst