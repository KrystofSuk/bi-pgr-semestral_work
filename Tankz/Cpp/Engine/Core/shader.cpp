#include "Engine/Core/shader.h"

sukkryst::Shader::Shader()
{
}

sukkryst::Shader::Shader(const std::string &vertPath, const std::string &fragPath)
{
	std::vector<GLuint> shaders;
	shaders.reserve(2);
	shaders.emplace_back(pgr::createShaderFromFile(GL_VERTEX_SHADER, vertPath));
	shaders.emplace_back(pgr::createShaderFromFile(GL_FRAGMENT_SHADER, fragPath));
	_id = pgr::createProgram(shaders);

	GetAttribLocation("position");
	GetAttribLocation("normal");
	GetAttribLocation("texCoord");
}

void sukkryst::Shader::Use() const
{
	glUseProgram(_id);
}

void sukkryst::Shader::SetFloat3f(const std::string &name, const glm::vec3 &value)
{
	glUniform3fv(GetLocation(name), 1, glm::value_ptr(value));
}

void sukkryst::Shader::SetFloat4f(const std::string &name, const glm::vec4 &value)
{
	glUniform4fv(GetLocation(name), 1, glm::value_ptr(value));
}

void sukkryst::Shader::SetFloatMatrix4f(const std::string &name, const glm::mat4 &value)
{
	glUniformMatrix4fv(GetLocation(name), 1, GL_FALSE, glm::value_ptr(value));
}

void sukkryst::Shader::SetFloat(const std::string &name, const float &value)
{
	glUniform1f(GetLocation(name), value);
}

void sukkryst::Shader::SetInt(const std::string &name, const int &value)
{
	glUniform1i(GetLocation(name), value);
}

void sukkryst::Shader::SetBool(const std::string &name, const bool &value)
{
	glUniform1i(GetLocation(name), (int)value);
}

GLuint sukkryst::Shader::GetAttribLocation(const std::string &name)
{
	if (_locations.find(name) == _locations.end())
	{
		_locations[name] = glGetAttribLocation(_id, name.c_str());
		CHECK_GL_ERROR();
	}
	return _locations.at(name);
}

GLuint sukkryst::Shader::GetLocation(const std::string &name)
{
	if (_locations.find(name) == _locations.end())
	{
		_locations[name] = glGetUniformLocation(_id, name.c_str());
	}
	return _locations.at(name);
}

sukkryst::Shader::~Shader()
{
}
