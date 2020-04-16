#include "..\..\Headers\Engine\resources.h"

Resources::Resources()
{
}

void Resources::AddShader(const std::string& name, const std::string& vertPath, const std::string& fragPath)
{
	_shaders.LoadShader(name, vertPath, fragPath);
}

void Resources::AddMesh(const std::string& name, const std::string& filename, const std::string& shaderName)
{
	_meshes.LoadMesh(name, filename, _shaders.GetShader(shaderName));
}

void Resources::AddMaterial(const std::string& name, const std::string& shaderName)
{
	_materials.LoadMaterial(name, _shaders.GetShader(shaderName));
}

Material* Resources::GetMaterial(const std::string& name) const
{
	return _materials.GetMaterial(name);
}

Mesh* Resources::GetMesh(const std::string& name) const
{
	return _meshes.GetMesh(name);
}

Shader* Resources::GetShader(const std::string& name) const
{
	return _shaders.GetShader(name);
}

Resources::~Resources()
{
}
