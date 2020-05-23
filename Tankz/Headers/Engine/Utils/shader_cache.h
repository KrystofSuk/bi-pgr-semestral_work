#pragma once

#include <unordered_map>
#include <string>

#include "Engine/Core/shader.h"

namespace sukkryst {

	/**
	 * @brief Shader cache class for storing loaded shaders
	 * 
	 */
	class ShaderCache {
	private:
		std::unordered_map<std::string, Shader*> _shaderCache;
	public:
		/**
		 * @brief Construct a new Shader Cache object
		 * 
		 */
		ShaderCache();

		/**
		 * @brief Loades single shader and packages it with certain name
		 * 
		 * @param name of packaged shader
		 * @param vertPath path to vertex part
		 * @param fragPath path to fragment path
		 */
		void LoadShader(const std::string& name, const std::string& vertPath, const std::string& fragPath);

		/**
		 * @brief Get the Shader object
		 * 
		 * @param name of desired shader package
		 * @return Shader* pointer to shader
		 */
		Shader* GetShader(const std::string& name) const;

		/**
		 * @brief Destroy the Shader Cache object
		 * 
		 */
		~ShaderCache();
	};

}