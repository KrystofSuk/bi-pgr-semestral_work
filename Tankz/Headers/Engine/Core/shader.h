#pragma once

#include <unordered_map>
#include <string>
#include <pgr.h>

namespace sukkryst {

	/**
	 * @brief Shader class to represent shader data and set its uniforms and others
	 * 
	 */
	class Shader {
		GLuint _id;
		std::unordered_map<std::string, int> _locations;
		
		/**
		 * @brief Get the the attrib location for specific name 
		 * 
		 * @param name of the node
		 * @return GLuint id of the node
		 */
		GLuint GetAttribLocation(const std::string& name);
	public:

		/**
		 * @brief Construct a new Shader
		 * 
		 */
		Shader();

		/**
		 * @brief Construct a new Shader object with given paths
		 * 
		 * @param vertPath path to vertex shader
		 * @param fragPath path to fragment shader
		 */
		Shader(const std::string& vertPath, const std::string& fragPath);

		/**
		 * @brief Get the specific location of the node with specific name
		 * 
		 * @param name of node
		 * @return GLuint id of the node
		 */
		GLuint GetLocation(const std::string& name);

		/**
		 * @brief Method to use this shader in rendering
		 * 
		 */
		void Use() const;

		/**
		 * @brief Set the 3-float uniform via vec3
		 * 
		 * @param name of node
		 * @param value of node
		 */
		void SetFloat3f(const std::string& name, const glm::vec3& value);
		
		/**
		 * @brief Set the 4-float uniform via vec4
		 * 
		 * @param name of node
		 * @param value of node
		 */
		void SetFloat4f(const std::string& name, const glm::vec4& value);
		
		/**
		 * @brief Set the 4x4float matrix uniform via mat4
		 * 
		 * @param name of node
		 * @param value of node
		 */
		void SetFloatMatrix4f(const std::string& name, const glm::mat4& value);
		
		/**
		 * @brief Set the 1-float uniform via float
		 * 
		 * @param name of node
		 * @param value of node
		 */
		void SetFloat(const std::string& name, const float& value);
		
		/**
		 * @brief Set the 1-int uniform via int
		 * 
		 * @param name of node
		 * @param value of node
		 */
		void SetInt(const std::string& name, const int& value);
		
		/**
		 * @brief Set the "bool" representation of int uniform
		 * 
		 * @param name of node
		 * @param value of node
		 */
		void SetBool(const std::string& name, const bool& value);

		/**
		 * @brief Destroy the Shader object
		 * 
		 */
		virtual ~Shader();
	};

}