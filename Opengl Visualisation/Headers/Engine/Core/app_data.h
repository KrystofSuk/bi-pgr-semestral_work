#pragma once

#include <string>

namespace sukkryst
{

	/**
	 * @brief Basic app data representation for window size...
	 * 
	 */
	struct AppData
	{
		int width;
		int height;
		int tickRate;
		int drawRate;
		std::string name;

		bool freeCamera = true;
	};
} // namespace sukkryst