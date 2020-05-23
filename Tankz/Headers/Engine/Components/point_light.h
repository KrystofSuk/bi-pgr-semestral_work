#pragma once
#include "Engine/Components/light.h"

namespace sukkryst
{

	struct PointLight : public Light
	{
		PointLight();
		void ProcessLight(Shader *shader, const std::string &index = "");
	};

} // namespace sukkryst
