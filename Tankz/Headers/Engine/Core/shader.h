#pragma once

#include <unordered_map>
#include <string>
#include <pgr.h>

class Shader {
	GLuint _id;
	std::unordered_map<std::string, int> _locations;
	GLuint GetAttribLocation(const std::string& name);

public:
	Shader();
	Shader(const std::string& vertPath, const std::string& fragPath);

	GLuint GetLocation(const std::string& name);

	void Use() const;
	
	void SetFloat3f(const std::string& name, const glm::vec3& value);
	void SetFloat4f(const std::string& name, const glm::vec4& value);
	void SetFloatMatrix4f(const std::string& name, const glm::mat4& value);
	void SetFloat(const std::string& name, const float& value);
	void SetInt(const std::string& name, const int& value);
	void SetBool(const std::string& name, const bool& value);

	virtual ~Shader();
};