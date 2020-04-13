#pragma once
#include <vector>

#include "../component.h"
#include "transform.h"
#include "../shader.h"

class Mesh {
public:
	GLuint vao, vbo, ebo;
	unsigned int faces, vert;
	Mesh(float* verts, float size, Shader * shader);
	Mesh(const aiScene* scene, Shader * shader);
};

class MeshRenderer : public Component {
private:
	Shader * _shader;
	GLuint _texture;
	Mesh * _mesh;
public:
	MeshRenderer(float * verts, float size, Shader * shader);
	MeshRenderer(const std::string& scene, Shader * shader);

	void Draw();
		
	std::string Print() const;

	friend std::ostream& operator<<(std::ostream& out, const MeshRenderer& renderer);

	~MeshRenderer();
};


