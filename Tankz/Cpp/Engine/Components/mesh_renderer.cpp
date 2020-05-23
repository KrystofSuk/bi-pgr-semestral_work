#include "Engine/Components/mesh_renderer.h"
#include "Engine/Core/app_data.h"

sukkryst::MeshRenderer::MeshRenderer(Mesh *mesh, Material *material) : Component("MeshRenderer")
{
	_mesh = mesh;
	_material = material;
}

void sukkryst::MeshRenderer::Draw(const glm::mat4 &p, const glm::mat4 &v, const LightData &lightData)
{
	glm::mat4 m = glm::translate(glm::mat4(1.0f), transform->position);
	m = glm::scale(m, transform->size);
	m = glm::rotate(m, glm::radians(transform->rotation[0]), glm::vec3(1, 0, 0));
	m = glm::rotate(m, glm::radians(transform->rotation[1]), glm::vec3(0, 1, 0));
	m = glm::rotate(m, glm::radians(transform->rotation[2]), glm::vec3(0, 0, 1));

	glm::mat4 PVM = p * v * m;

	const glm::mat4 modelRotationMatrix = glm::mat4(
		m[0],
		m[1],
		m[2],
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

	glm::mat4 normalMatrix = glm::transpose(glm::inverse(modelRotationMatrix));

	Shader *shader = _material->shader;

	shader->Use();
	//shader->SetFloat4f("input_color", glm::vec4(_material->diffuse, 1.0));
	shader->SetFloatMatrix4f("PVM", PVM);
	shader->SetFloatMatrix4f("V", v);
	shader->SetFloatMatrix4f("M", m);
	shader->SetFloatMatrix4f("NM", normalMatrix);

	shader->SetFloat("time", 0.001f * (float)glutGet(GLUT_ELAPSED_TIME));

	int point = 0;
	int spot = 0;

	for (auto &l : lightData.lights)
	{
		if (l->type == 0)
			l->ProcessLight(shader);
		if (l->type == 1)
		{
			l->ProcessLight(shader, std::to_string(point));
			point++;
		}
		if (l->type == 2)
		{
			l->ProcessLight(shader, std::to_string(spot));
			spot++;
		}
	}

	shader->SetInt("point", point);
	shader->SetInt("spot", spot);

	shader->SetFloat3f("mat.ambient", _material->emission);
	shader->SetFloat3f("mat.diffuse", _material->diffuse);
	shader->SetFloat3f("mat.specular", _material->specular);
	shader->SetFloat("mat.shininess", _material->shininess);
	if (_material->diffuseMap)
		shader->SetInt("mat.diffTex", 1);
	if (!_material->diffuseMap)
		shader->SetInt("mat.diffTex", 0);

	shader->SetFloat3f("fog.color", lightData.fogColor);
	shader->SetFloat("fog.inte", lightData.fogIntensity);
	shader->SetFloat("fog.ramp", lightData.fogRamp);
	shader->SetFloat("fog.inte_h", lightData.fogHeightIntensity);
	shader->SetFloat("fog.ramp_h", lightData.fogHeightRamp);
	shader->SetFloat("fog.amount", lightData.fogAmount);

	shader->SetFloat("dir_amou", lightData.dirAmount);

	if (_mesh->texture != 0)
	{
		shader->SetInt("texSampler", 0);
		glActiveTexture(GL_TEXTURE0 + 0);
		glBindTexture(GL_TEXTURE_2D, _mesh->texture);
	}

	glBindVertexArray(_mesh->vao);

	GameObject *go = (GameObject *)(gameObject);
	glStencilFunc(GL_ALWAYS, go->id, -1);

	glDrawElements(GL_TRIANGLES, _mesh->faces * 3, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

std::string sukkryst::MeshRenderer::Print() const
{
	return name;
}

sukkryst::MeshRenderer::~MeshRenderer()
{
}

std::ostream &operator<<(std::ostream &out, const sukkryst::MeshRenderer &renderer)
{
	out << renderer.Print() << std::endl;
	return out;
}
