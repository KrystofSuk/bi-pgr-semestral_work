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
	lightData.lights.emplace_back(light);
}

void Scene::Click(const unsigned char& id)
{
	for (auto& it : _gameObjects)
		it.second->OnClick(id);
}

GameObject* Scene::GetGameObject(const std::string& name) const
{
	return _gameObjects.at(name);
}

void Scene::Clear()
{
	for (auto& it : _gameObjects)
		delete it.second;

	_renderers.clear();
	lightData.lights.clear();
}

void Scene::Update()
{
	for (auto& go : _gameObjects)
	{
		go.second->Update();
	}
}

void Scene::Render(const glm::mat4& p, const glm::mat4& v, bool inMode)
{
	if (inMode == true) {
		for (auto& rndr : _renderers)
		{
			GameObject* t = (GameObject*)rndr->gameObject;
			if (t->name != "Terrain")
			{
				rndr->Draw(p, v, lightData);
			}
		}
	}
	else {
		for (auto& rndr : _renderers) {
			GameObject* t = (GameObject*)rndr->gameObject;
			if (t->name != "Room")
			{
				rndr->Draw(p, v, lightData);
			}
		}
	}
}

Scene::~Scene()
{
	Clear();
}

