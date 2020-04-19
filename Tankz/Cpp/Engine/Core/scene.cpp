#include "Engine/Core/scene.h"

Scene::Scene()
{

}

void Scene::AddGameObject(GameObject* gameObject)
{
	_gameObjects[gameObject->name] = gameObject;
	if (gameObject->name == "Camera")
		camera = gameObject;
}

void Scene::AddRenderer(MeshRenderer* renderer)
{
	_renderers.emplace_back(renderer);
}

void Scene::AddLight(Light* light)
{
	_lights.emplace_back(light);
}

void Scene::Render(const glm::mat4& p, const glm::mat4& v)
{
	for (auto& rndr : _renderers)
	{
		rndr->Draw(p, v, _lights);
	}
}

Scene::~Scene()
{
	for (auto& it : _gameObjects) 
		delete it.second;
}

