#include "Engine/Utils/mesh_cache.h"

sukkryst::MeshCache::MeshCache()
{
}

void sukkryst::MeshCache::LoadMesh(const std::string &name, const std::string &fileName, Shader *shader)
{
	Mesh *mesh = new Mesh(fileName, shader);
	_meshCache[name] = mesh;
}

sukkryst::Mesh *sukkryst::MeshCache::GetMesh(const std::string &name) const
{
	return _meshCache.at(name);
}

sukkryst::MeshCache::~MeshCache()
{
	auto it = _meshCache.begin();
	while (it != _meshCache.end())
	{
		delete it->second;
		it++;
	}
}
