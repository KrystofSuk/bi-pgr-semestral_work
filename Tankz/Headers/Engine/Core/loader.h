#pragma once
#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <Engine/Core/resources.h>
#include <Engine/Core/app_data.h>
#include <Engine/Core/scene.h>

namespace sukkryst {

	struct Loader {
		static void LoadApp(const std::string& appPath, AppData& data);
		static void LoadResources(const std::string& configPath, Resources& resources);
		static void LoadScene(const std::string& scenePath, Scene& scene, Resources& resources);
	};

}