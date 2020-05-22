#include "Engine/Utils/shader_cache.h"

sukkryst::ShaderCache::ShaderCache()
{
}

void sukkryst::ShaderCache::LoadShader(const std::string& name, const std::string& vertPath, const std::string& fragPath)
{
	Shader* shr = new Shader(vertPath, fragPath);
	_shaderCache[name] = shr;
}

sukkryst::Shader* sukkryst::ShaderCache::GetShader(const std::string& name) const
{
	return _shaderCache.at(name);
}

sukkryst::ShaderCache::~ShaderCache()
{
	auto it = _shaderCache.begin();
	while (it != _shaderCache.end())
	{
		delete it->second;
		it++;
	}
}
