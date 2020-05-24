#pragma once

#include "Engine/Utils/shader_cache.h"
#include "Engine/Utils/mesh_cache.h"
#include "Engine/Utils/material_cache.h"

namespace sukkryst
{

	/**
	 * @brief Resources representation including shader, mesh and material caches
	 * 
	 */
	class Resources
	{
	private:
		ShaderCache _shaders;
		MeshCache _meshes;
		MaterialCache _materials;

	public:
		/**
		 * @brief Construct a new Resources
		 * 
		 */
		Resources();

		/**
		 * @brief Adds new shader to resources
		 * 
		 * @param name of the shader
		 * @param vertPath path to vertex shader
		 * @param fragPath path to fragment shader
		 */
		void AddShader(const std::string &name, const std::string &vertPath, const std::string &fragPath);

		/**
		 * @brief Adds new mesh to resources
		 * 
		 * @param name of mesh
		 * @param fileName path to mesh
		 * @param shaderName name of specific shader
		 */
		void AddMesh(const std::string &name, const std::string &fileName, const std::string &shaderName);

		/**
		 * @brief Adds new material to resources
		 * 
		 * @param name of material
		 * @param shaderName name of used shader
		 */
		void AddMaterial(const std::string &name, const std::string &shaderName);

		/**
		 * @brief Get the specific material
		 * 
		 * @param name of material
		 * @return Material* pointer to cached material
		 */
		Material *GetMaterial(const std::string &name) const;

		/**
		 * @brief Get the specific mesh
		 * 
		 * @param name of mesh
		 * @return Mesh* pointer to cached mesh
		 */
		Mesh *GetMesh(const std::string &name) const;

		/**
		 * @brief Get the specific shader
		 * 
		 * @param name of shader
		 * @return Shader* pointer to cached shader
		 */
		Shader *GetShader(const std::string &name) const;

		/**
		 * @brief Destroy the Resources
		 * 
		 */
		~Resources();
	};

} // namespace sukkryst