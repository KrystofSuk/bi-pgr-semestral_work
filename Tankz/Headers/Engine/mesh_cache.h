#pragma once

#include "Components/mesh_renderer.h"
#include <unordered_map>
#include <string>

class MeshCache {
private:
	std::unordered_map<std::string, Mesh*> _meshCache;
public:
	MeshCache();
	void LoadMesh(const std::string& name, const std::string& filename, Shader * shader);
	Mesh* GetMesh(const std::string& name) const;
	~MeshCache();
};