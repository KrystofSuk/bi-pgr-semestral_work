#pragma once

#include <unordered_map>
#include <string>

#include "Engine/Components/mesh_renderer.h"

namespace sukkryst {

	/**
	 * @brief Cache of meshes and their names
	 * 
	 */
	class MeshCache {
	private:
		std::unordered_map<std::string, Mesh*> _meshCache;
	public:

		/**
		 * @brief Construct a new Mesh Cache object
		 * 
		 */
		MeshCache();

		/**
		 * @brief Loades the mesh and holds it with certain name
		 * 
		 * @param name saved name of mesh
		 * @param fileName file where is .obj located
		 * @param shader shader to pair the mesh with
		 */
		void LoadMesh(const std::string& name, const std::string& fileName, Shader* shader);

		/**
		 * @brief Get the Mesh object
		 * 
		 * @param name saved name in cache
		 * @return Mesh* pointer to saved mesh
		 */
		Mesh* GetMesh(const std::string& name) const;

		/**
		 * @brief Destroy the Mesh Cache object
		 * 
		 */
		~MeshCache();
	};

}
