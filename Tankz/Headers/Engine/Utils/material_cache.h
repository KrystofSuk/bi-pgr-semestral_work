#pragma once

#include <unordered_map>
#include <string>

#include "Engine/Core/material.h"
#include "Engine/Core/shader.h"

namespace sukkryst {

	/**
	 * @brief Cache for materials and their names
	 * 
	 */
	class MaterialCache {
	private:
		std::unordered_map<std::string, Material*> _materialCache;
	public:

		/**
		 * @brief Construct a new Material Cache object
		 * 
		 */
		MaterialCache();

		/**
		 * @brief Constructs the new material with name and specified shader
		 * 
		 * @param name desired material name
		 * @param shader desired shader of the material
		 */
		void LoadMaterial(const std::string& name, Shader* shader);

		/**
		 * @brief Get the Material object
		 * 
		 * @param name of material in cache
		 * @return Material* pointer to cached material
		 */
		Material* GetMaterial(const std::string& name) const;

		/**
		 * @brief Destroy the Material Cache object
		 * 
		 */
		~MaterialCache();
	};

}