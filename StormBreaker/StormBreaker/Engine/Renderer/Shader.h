#ifndef SHADER_H
#define SHADER_H

#include <framework.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_map>

//GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "OpenGLErrorHandler.h"


struct SimpleShader
{
	unsigned int m_shaderId = 0;
	GLenum m_type;
	std::string m_source;
	SimpleShader(GLenum type) :m_shaderId(0),m_type(type) {}
	SimpleShader(GLenum type, std::string source) :m_shaderId(0),m_type(type), m_source(source) {}
};




class Shader
{

private:
	void LoadShaderCode(const GLchar* vertexPath, GLenum& type);
	void CompileShaderCode(SimpleShader& shader);
	mutable std::unordered_map< std::string, int> m_UniformLocations;

	//Uniform Mapping methods
	int GetUniformLocation(const std::string& name) const;
	int GetUniformBufferIndex(const std::string& name) const;

public:
	//Program ID
	unsigned int m_programID = 0;
	SimpleShader m_vertexShader;
	SimpleShader m_fragmentShader;

	//Constructor to read and build the shader
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);

	void LinkShaders();

	//Use the shader
	void UseShader() const;

	//Utility uniform functions
	
	void SetBool(const std::string& name, bool value) const;
	void SetInt(const std::string& name, int value) const;
	void SetFloat(const std::string& name, float value) const;
	void SetFloat4(const std::string& name, float r, float g, float b, float a);
	void SetVec2(const std::string& name, const glm::vec2& value) const;
	void SetVec2(const std::string& name, float x, float y) const;
	void SetVec3(const std::string& name, const glm::vec3& value) const;
	void SetVec3(const std::string& name, float x, float y, float z) const;
	void SetVec4(const std::string& name, const glm::vec4& value) const;
	void SetVec4(const std::string& name, float x, float y, float z, float w) const;
	void SetMat2(const std::string& name, const glm::mat2& mat) const;
	void SetMat3(const std::string& name, const glm::mat3& mat) const;
	void SetMat4(const std::string& name, const glm::mat4& mat) const;
	void SetUniformBlock(const std::string& name, const unsigned int slot = 0);
	
};

#endif //!SHADER_H