#pragma once
#include <vector>

#include "../component.h"
#include "transform.h"
#include "../shader.h"
#include "../material.h"

class Mesh {
public:
	GLuint vao, vbo, ebo;
	GLuint _texture;
	unsigned int faces, vert;
	Mesh(const std::string& fileName, Shader * shader);
};

class MeshRenderer : public Component {
private:
	Material * _material;
	Mesh * _mesh;
public:
	MeshRenderer(Mesh* mesh, Material* material);

	void Draw(const glm::mat4& p, const glm::mat4& v, Transform* t);
		
	std::string Print() const;

	friend std::ostream& operator<<(std::ostream& out, const MeshRenderer& renderer);

	~MeshRenderer();
};


