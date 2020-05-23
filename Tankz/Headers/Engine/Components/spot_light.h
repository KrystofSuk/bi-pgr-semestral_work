#pragma once

#include "Engine/Components/light.h"

namespace sukkryst
{

	struct SpotLight : public Light
	{
		SpotLight();
		void ProcessLight(Shader *shader, const std::string &index = "");
	};

} // namespace sukkryst