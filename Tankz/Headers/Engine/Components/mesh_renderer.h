#pragma once

#include <vector>
#include <string>

#include "Engine/Core/component.h"
#include "Engine/Core/game_object.h"
#include "Engine/Core/transform.h"
#include "Engine/Core/shader.h"
#include "Engine/Core/material.h"
#include "Engine/Core/mesh.h"
#include "Engine/Components/light.h"
#include <Engine\Core\light_data.h>

namespace sukkryst
{

	/**
	 * @brief Mesh renderer component to render meshes with specific materials
	 * 
	 */
	class MeshRenderer : public Component
	{
	private:
		Material *_material;
		Mesh *_mesh;

	public:
		
		/**
		 * @brief Construct a new Mesh Renderer
		 * 
		 * @param mesh to render
		 * @param material to render the mesh with
		 */
		MeshRenderer(Mesh *mesh, Material *material);

		/**
		 * @brief Draw the mesh with specific projection and view matrix + lightning
		 * 
		 * @param p matrix
		 * @param v matrix
		 * @param lightData to send to shader
		 */
		void Draw(const glm::mat4 &p, const glm::mat4 &v, const LightData &lightData);

		/**
		 * @brief Destroy the Mesh Renderer object
		 * 
		 */
		~MeshRenderer();
	};

} // namespace sukkryst