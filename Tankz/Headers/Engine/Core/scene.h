#pragma once
#include <unordered_map>
#include <string>
#include <vector>

#include <Engine/Core/game_object.h>
#include <Engine/Components/mesh_renderer.h>
#include <Engine/Components/light.h>
#include <Engine\Core\light_data.h>

namespace sukkryst {

	/**
	 * @brief Scene representation class for rendering, gameobjects and lights
	 * 
	 */
	class Scene {
		std::unordered_map<std::string, GameObject*> _gameObjects;
		std::vector<MeshRenderer*> _renderers;
	public:

		/**
		 * @brief Lightning data for current scene so we can have per scene lightning
		 * 
		 */
		LightData lightData;

		/**
		 * @brief Camera pointer for faster camera access
		 * 
		 */
		GameObject* camera;

		/**
		 * @brief Construct a new Scene object
		 * 
		 */
		Scene();

		/**
		 * @brief Add new gameobject to scene
		 * 
		 * @param gameObject to add
		 */
		void AddGameObject(GameObject* gameObject);

		/**
		 * @brief Add specific meshrenderer to scene to render in Render method
		 * 
		 * @param renderer to add
		 */
		void AddRenderer(MeshRenderer* renderer);

		/**
		 * @brief Add light to the scene
		 * 
		 * @param light to add
		 */
		void AddLight(Light* light);

		/**
		 * @brief Process click in gameobject with specific id
		 * 
		 * @param id of the gameobject
		 */
		void Click(const unsigned char& id);

		/**
		 * @brief Get specific gameobject by his name
		 * 
		 * @param name of desired gameobject
		 * @return GameObject* pointer to the gameobject
		 */
		GameObject* GetGameObject(const std::string& name) const;

		/**
		 * @brief Clears the scene
		 * 
		 */
		void Clear();

		/**
		 * @brief Updates the scene = updates all gameobjects
		 * 
		 */
		void Update();

		/**
		 * @brief Render all mesh renderers with p and v matrix + specific inMode (if inside or outside)
		 * 
		 * @param p matrix
		 * @param v matrix
		 * @param inMode if scene is inside or outside (terrain or indoor)
		 */
		void Render(const glm::mat4& p, const glm::mat4& v, bool inMode);

		/**
		 * @brief Destroy the Scene object
		 * 
		 */
		~Scene();
	};

}