#pragma once

#include <vector>
#include <string>

#include "Engine/Core/component.h"
#include "Engine/Core/transform.h"
#include "Engine/Core/shader.h"
#include "Engine/Core/material.h"
#include "Engine/Core/mesh.h"
#include "Engine/Components/light.h"

class MeshRenderer : public Component {
private:
	Material * _material;
	Mesh* _mesh;
public:
	MeshRenderer(Mesh* mesh, Material* material);

	void Draw(const glm::mat4& p, const glm::mat4& v, std::vector<Light *> lights);
		
	std::string Print() const;

	friend std::ostream& operator<<(std::ostream& out, const MeshRenderer& renderer);

	~MeshRenderer();
};


