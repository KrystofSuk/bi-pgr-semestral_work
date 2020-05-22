#include "Engine/Utils/material_cache.h"


sukkryst::MaterialCache::MaterialCache()
{
}

void sukkryst::MaterialCache::LoadMaterial(const std::string& name, Shader* shader)
{
	Material* material = new Material(name, shader);
	_materialCache[name] = material;
}

sukkryst::Material* sukkryst::MaterialCache::GetMaterial(const std::string& name) const
{
	return _materialCache.at(name);
}

sukkryst::MaterialCache::~MaterialCache()
{
	auto it = _materialCache.begin();
	while (it != _materialCache.end())
	{
		delete it->second;
		it++;
	}
}
