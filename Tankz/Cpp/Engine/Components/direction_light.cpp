#include "Engine/Components/direction_light.h"
#include "Engine/Core/game_object.h"

sukkryst::DirectionLight::DirectionLight() : Component("DirectionLight")
{
	type = 0;
}

void sukkryst::DirectionLight::ProcessLight(Shader *shader, const std::string &index)
{
	glm::vec3 pos = transform->position;
	if (on)
	{
		shader->SetFloat3f("dir.diffuse", diffuse * intensity);
		shader->SetFloat3f("dir.ambient", ambient * intensity);
		shader->SetFloat3f("dir.specular", specular * intensity);
	}
	if (!on)
	{
		shader->SetFloat3f("dir.diffuse", diffuse * 0.0f);
		shader->SetFloat3f("dir.ambient", ambient * 0.0f);
		shader->SetFloat3f("dir.specular", specular * 0.0f);
	}
	shader->SetFloat3f("dir.pos", pos);
	shader->SetFloat("dir.shininess", shininess);
}
