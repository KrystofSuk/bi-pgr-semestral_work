#pragma once

#include "material.h"
#include "shader.h"
#include <unordered_map>
#include <string>

class MaterialCache {
private:
	std::unordered_map<std::string, Material*> _materialCache;
public:
	MaterialCache();
	void LoadMaterial(const std::string& name, Shader* shader);
	Material* GetMaterial(const std::string& name) const;
	~MaterialCache();
};