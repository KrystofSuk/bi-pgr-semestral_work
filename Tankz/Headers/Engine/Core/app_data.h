#pragma once

#include <string>

namespace sukkryst {

	struct AppData
	{
		int width;
		int height;
		int tickRate;
		int drawRate;
		std::string name;

		bool freeCamera = true;
		static float time;
		static float GetTime() {
			return time;
		}
	};

}