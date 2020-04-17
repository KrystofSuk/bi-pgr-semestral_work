#pragma once

#include <pgr.h>
#include <iostream>

#include "Engine/Core/shader.h"

struct Mesh {
	GLuint vao, vbo, ebo;
	GLuint texture;
	unsigned int faces, vert;
	Mesh(const std::string& fileName, Shader* shader);
};