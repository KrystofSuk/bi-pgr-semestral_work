#pragma once

#include <unordered_map>
#include <string>

#include "Engine/Core/shader.h"

namespace sukkryst {

	class ShaderCache {
	private:
		std::unordered_map<std::string, Shader*> _shaderCache;
	public:
		ShaderCache();
		void LoadShader(const std::string& name, const std::string& vertPath, const std::string& fragPath);
		Shader* GetShader(const std::string& name) const;
		~ShaderCache();
	};

}