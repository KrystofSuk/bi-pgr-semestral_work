#pragma once

#include "Engine/Utils/shader_cache.h"
#include "Engine/Utils/mesh_cache.h"
#include "Engine/Utils/material_cache.h"

class Resources {
private:
	ShaderCache _shaders;
	MeshCache _meshes;
	MaterialCache _materials;
public:
	Resources();

	void AddShader(const std::string& name, const std::string& vertPath, const std::string& fragPath);
	void AddMesh(const std::string& name, const std::string& filename, const std::string& shaderName);
	void AddMaterial(const std::string& name, const std::string& shaderName);

	Material* GetMaterial(const std::string& name) const;
	Mesh* GetMesh(const std::string& name) const;
	Shader* GetShader(const std::string& name) const;

	~Resources();
};