
#include "..\..\..\Headers\Engine\Core\loader.h"
#include "ThirdParty/json.hpp"
#include "Engine\Components\direction_light.h"
#include "Engine\Components\point_light.h"
#include "Engine\Components\spot_light.h"
#include <Engine\Components\Custom\day_night.h>
#include "Engine\Components\Custom\collision_box.h"

using json = nlohmann::json;

namespace sukkryst {

	glm::vec3 CreateVec3(const std::string& v) {
		std::stringstream ss(v);
		std::string value;
		float* floats = new float[3];
		int i = 0;
		while (std::getline(ss, value, ',')) {
			floats[i] = atof(value.c_str());
			i++;
		}

		return glm::vec3(floats[0], floats[1], floats[2]);
	}

	float CreateFloat(const std::string& v) {
		return atof(v.c_str());
	}

}

void sukkryst::Loader::LoadApp(const std::string& appPath, AppData& data)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	std::cout << "---------LOADING APPDATA---------" << std::endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);

	std::ifstream in(appPath);
	json conf;
	in >> conf;

	std::string name = conf.at("name");
	data.name = name;
	data.width = conf.at("width");
	data.height = conf.at("height");
	data.tickRate = conf.at("update_time");
	data.drawRate = conf.at("draw_time");

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	std::cout << "---------LOADING DONE---------" << std::endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void sukkryst::Loader::LoadResources(const std::string& configPath, Resources& resources)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	std::cout << "---------LOADING RESOURCES---------" << std::endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);

	std::ifstream in(configPath);
	json conf;
	in >> conf;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	std::cout << "---------SHADERS---------" << std::endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
	//SHADER LOADING
	for (json::iterator it = conf.at("Shaders").begin(); it != conf.at("Shaders").end(); ++it) {
		resources.AddShader((*it).at("name"), (*it).at("vert"), (*it).at("frag"));
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	std::cout << "---------MATERIALS---------" << std::endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
	//MATERIAL LOADING
	for (json::iterator it = conf.at("Materials").begin(); it != conf.at("Materials").end(); ++it) {
		std::string name = (*it).at("name");
		resources.AddMaterial(name, (*it).at("shader"));

		resources.GetMaterial(name)->diffuse = CreateVec3((*it).at("diffuse"));
		resources.GetMaterial(name)->specular = CreateVec3((*it).at("specular"));
		resources.GetMaterial(name)->emission = CreateVec3((*it).at("emission"));
		resources.GetMaterial(name)->shininess = CreateFloat((*it).at("shininess"));

		if ((*it).at("diffuseMap") == "true")
			resources.GetMaterial(name)->diffuseMap = true;
		if ((*it).at("diffuseMap") == "false")
			resources.GetMaterial(name)->diffuseMap = false;
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	std::cout << "---------MESHES---------" << std::endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
	//MESH LOADING
	for (json::iterator it = conf.at("Meshes").begin(); it != conf.at("Meshes").end(); ++it) {
		resources.AddMesh((*it).at("name"), (*it).at("path"), (*it).at("shader"));
	}


	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	std::cout << "---------LOADING DONE---------" << std::endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void sukkryst::Loader::LoadScene(const std::string& scenePath, Scene& scene, Resources& resources)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	std::cout << "---------LOADING SCENE---------" << std::endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);

	std::ifstream in(scenePath);
	json conf;
	in >> conf;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	std::cout << "---------LIGHTNNG---------" << std::endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);

	scene.lightData.fogDefaultColor = CreateVec3(conf.at("Lightning").at("fog_color"));
	scene.lightData.fogColor = CreateVec3(conf.at("Lightning").at("fog_color"));
	scene.lightData.fogIntensity = CreateFloat(conf.at("Lightning").at("fog_intensity"));
	scene.lightData.fogRamp = CreateFloat(conf.at("Lightning").at("fog_ramp"));
	scene.lightData.fogHeightIntensity = CreateFloat(conf.at("Lightning").at("height_intensity"));
	scene.lightData.fogHeightRamp = CreateFloat(conf.at("Lightning").at("height_ramp"));

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	std::cout << "---------GAME OBJECTS---------" << std::endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);

	for (json::iterator it = conf.at("GameObjects").begin(); it != conf.at("GameObjects").end(); ++it) {
		GameObject* gameObject = new GameObject((*it).at("name"));
		gameObject->transform->Move(CreateVec3((*it).at("position")));
		gameObject->transform->Rotate(CreateVec3((*it).at("rotation")));
		gameObject->transform->Scale(CreateVec3((*it).at("scale")));
		for (json::iterator it2 = (*it).at("components").begin(); it2 != (*it).at("components").end(); ++it2) {
			std::string name = (*it2).at("name");

			if (name == "MeshRenderer") {
				MeshRenderer* c = new MeshRenderer(resources.GetMesh((*it2).at("mesh")), resources.GetMaterial((*it2).at("material")));
				gameObject->AddComponent(c);
				scene.AddRenderer(c);
			}
			if (name == "DirectionLight") {
				DirectionLight* c = new DirectionLight();
				c->diffuse = CreateVec3((*it2).at("diffuse"));
				c->specular = CreateVec3((*it2).at("specular"));
				c->ambient = CreateVec3((*it2).at("ambient"));
				c->shininess = (*it2).at("shininess");
				c->intensity = (*it2).at("intensity");
				gameObject->AddComponent(c);
				scene.AddLight(c);
			}
			if (name == "PointLight") {
				PointLight* c = new PointLight();
				c->diffuse = CreateVec3((*it2).at("diffuse"));
				c->specular = CreateVec3((*it2).at("specular"));
				c->ambient = CreateVec3((*it2).at("ambient"));
				c->shininess = (*it2).at("shininess");
				c->intensity = (*it2).at("intensity");
				gameObject->AddComponent(c);
				scene.AddLight(c);
			}
			if (name == "SpotLight") {
				SpotLight* c = new SpotLight();
				c->diffuse = CreateVec3((*it2).at("diffuse"));
				c->specular = CreateVec3((*it2).at("specular"));
				c->ambient = CreateVec3((*it2).at("ambient"));
				c->shininess = (*it2).at("shininess");
				c->intensity = (*it2).at("intensity");
				gameObject->AddComponent(c);
				scene.AddLight(c);
			}
			if (name == "DayNight") {
				DayNight* c = new DayNight(scene);
				c->speed = CreateVec3((*it2).at("speed"));
				c->nightFogColor = CreateVec3((*it2).at("nightFogColor"));
				gameObject->AddComponent(c);
			}
			if (name == "CollisionBox") {
				CollisionBox* c = new CollisionBox(CreateVec3((*it2).at("size")));
				c->yMin = CreateFloat((*it2).at("min"));
				gameObject->AddComponent(c);
			}
		}

		scene.AddGameObject(gameObject);
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	std::cout << "---------LOADING DONE---------" << std::endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

