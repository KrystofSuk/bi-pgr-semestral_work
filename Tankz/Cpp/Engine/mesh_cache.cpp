#include "..\..\Headers\Engine\mesh_cache.h"

MeshCache::MeshCache()
{
}

void MeshCache::LoadMesh(const std::string& name, const std::string& filename, Shader* shader)
{
	Mesh* mesh = new Mesh(filename, shader);
	_meshCache[name] = mesh;
}

Mesh* MeshCache::GetMesh(const std::string& name) const
{
	return _meshCache.at(name);
}

MeshCache::~MeshCache()
{
	auto it = _meshCache.begin();
	while (it != _meshCache.end())
	{
		delete it->second;
		it++;
	}
}
