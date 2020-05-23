#pragma once
#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <Engine/Core/resources.h>
#include <Engine/Core/app_data.h>
#include <Engine/Core/scene.h>

namespace sukkryst
{

	/**
	 * @brief Config loader to load appdata, resources and scene json config files
	 * 
	 */
	struct Loader
	{

		/**
		 * @brief Loading app data json
		 * 
		 * @param appPath path to appdata file
		 * @param data object to fill info to
		 */
		static void LoadApp(const std::string &appPath, AppData &data);

		/**
		 * @brief Loading resources json
		 * 
		 * @param configPath path to resources file
		 * @param resources object to fill info to
		 */
		static void LoadResources(const std::string &configPath, Resources &resources);

		/**
		 * @brief Loading scene json
		 * 
		 * @param scenePath path to scene file
		 * @param scene object to fill info to
		 * @param resources object to get info from like meshes and shaders
		 */
		static void LoadScene(const std::string &scenePath, Scene &scene, Resources &resources);
	};

} // namespace sukkryst