#pragma once

#include <filesystem>

#include "pgr.h"
#include "Engine/Core/component.h"
#include "Engine/Core/shader.h"
#include "Engine/Core/transform.h"

namespace sukkryst {

	class Skybox : public Component {
	public:
		GLuint vao, vbo, ebo;
		GLuint texture;
		Shader* shader;
		unsigned int faces, vert;

		Skybox(const std::string filePath, Shader* shader);

		void Draw(const glm::mat4& p, const glm::mat4& v, Transform* c);

		std::string Print() const;

		friend std::ostream& operator<<(std::ostream& out, const Skybox& skybox);

		~Skybox();
	};

}