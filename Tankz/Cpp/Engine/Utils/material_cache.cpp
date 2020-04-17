#include "Engine/Utils/material_cache.h"


MaterialCache::MaterialCache()
{
}

void MaterialCache::LoadMaterial(const std::string& name, Shader* shader)
{
	Material* material = new Material(name, shader);
	_materialCache[name] = material;
}

Material* MaterialCache::GetMaterial(const std::string& name) const
{
	return _materialCache.at(name);
}

MaterialCache::~MaterialCache()
{
	auto it = _materialCache.begin();
	while (it != _materialCache.end())
	{
		delete it->second;
		it++;
	}
}
