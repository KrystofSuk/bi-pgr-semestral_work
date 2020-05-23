#include "Engine/Core/resources.h"

sukkryst::Resources::Resources()
{
}

void sukkryst::Resources::AddShader(const std::string& name, const std::string& vertPath, const std::string& fragPath)
{
	_shaders.LoadShader(name, vertPath, fragPath);
}

void sukkryst::Resources::AddMesh(const std::string& name, const std::string& fileBame, const std::string& shaderName)
{
	_meshes.LoadMesh(name, fileBame, _shaders.GetShader(shaderName));
}

void sukkryst::Resources::AddMaterial(const std::string& name, const std::string& shaderName)
{
	_materials.LoadMaterial(name, _shaders.GetShader(shaderName));
}

sukkryst::Material* sukkryst::Resources::GetMaterial(const std::string& name) const
{
	return _materials.GetMaterial(name);
}

sukkryst::Mesh* sukkryst::Resources::GetMesh(const std::string& name) const
{
	return _meshes.GetMesh(name);
}

sukkryst::Shader* sukkryst::Resources::GetShader(const std::string& name) const
{
	return _shaders.GetShader(name);
}

sukkryst::Resources::~Resources()
{
}
