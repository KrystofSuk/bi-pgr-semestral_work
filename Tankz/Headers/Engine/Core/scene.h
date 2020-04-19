#pragma once
#include <unordered_map>
#include <string>
#include <vector>

#include <Engine/Core/game_object.h>
#include <Engine/Components/mesh_renderer.h>
#include <Engine/Components/light.h>
#include <Engine\Core\light_data.h>

class Scene {
	std::unordered_map<std::string, GameObject*> _gameObjects;
	std::vector<MeshRenderer*> _renderers;
public:
	LightData lightData;

	GameObject * camera;

	Scene();
	void AddGameObject(GameObject* gameObject);
	void AddRenderer(MeshRenderer* renderer);
	void AddLight(Light* light);

	GameObject* GetGameObject(const std::string& name) const;

	void Clear();
	void Update();
	void Render(const glm::mat4& p, const glm::mat4& v);
	~Scene();
};