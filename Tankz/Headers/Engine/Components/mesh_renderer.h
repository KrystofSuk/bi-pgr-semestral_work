#pragma once
#include <vector>

#include "../component.h"
#include "transform.h"
#include "../shader.h"
#include "../material.h"
#include "../mesh.h"
#include "light.h"

class MeshRenderer : public Component {
private:
	Material * _material;
	Mesh* _mesh;
public:
	MeshRenderer(Mesh* mesh, Material* material);

	void Draw(const glm::mat4& p, const glm::mat4& v, Transform* t, std::vector<Light *> lights, Transform* c);
		
	std::string Print() const;

	friend std::ostream& operator<<(std::ostream& out, const MeshRenderer& renderer);

	~MeshRenderer();
};


