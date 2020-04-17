#pragma once

#include <unordered_map>
#include <string>

#include "Engine/Core/material.h"
#include "Engine/Core/shader.h"

class MaterialCache {
private:
	std::unordered_map<std::string, Material*> _materialCache;
public:
	MaterialCache();
	void LoadMaterial(const std::string& name, Shader* shader);
	Material* GetMaterial(const std::string& name) const;
	~MaterialCache();
};