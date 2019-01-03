#include "Shader.h"
#include <iostream>
#include<fstream>
#include<string>
#include<sstream>

#include "Renderer.h"



Shader::Shader(const std::string & filepath)
	:m_RendererId(0), m_filepath(filepath)
{
	ShaderProgramSource source = ParseShader("res/shaders/basic.shader");
	m_RendererId = CreateShader(source.VertexSource, source.FragmentSource);
}

Shader::~Shader()
{
	GLCall(glDeleteProgram(m_RendererId));
}

void Shader::Bind()
{
	GLCall(glUseProgram(m_RendererId));
}

void Shader::Unbind()
{
	GLCall(glUseProgram(0));
}

void Shader::SetUniform4f(const std::string & name, float r, float g, float b, float a)
{
	GLCall(glUniform4f(GetUniformLocation(name), r, g, b, a));
}

ShaderProgramSource Shader::ParseShader(const std::string & filepath)
{
	std::ifstream stream(filepath);
	enum class ShaderType {
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};
	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;
	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
				type = ShaderType::VERTEX;
			else if (line.find("fragment") != std::string::npos)
				type = ShaderType::FRAGMENT;
		}
		else
		{
			ss[(int)type] << line << '\n';
		}
	}

	return { ss[0].str(),ss[1].str() };
}

unsigned int Shader::CreateShader(const std::string & vertexShader, const std::string & fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

unsigned int Shader::CompileShader(unsigned int type, const std::string & source)
{
	unsigned int id = glCreateShader(type);
	const char * src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char*  message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compile of type " << ((type == GL_VERTEX_SHADER) ? "Vertex" : "Fragment") << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;
	}
	return id;
}

int Shader::GetUniformLocation(const std::string & name)
{
	int location;
	if (m_UniformLocations.find(name) != m_UniformLocations.end())
		return m_UniformLocations[name];
	else
		GLCall(location = glGetUniformLocation(m_RendererId, "u_Color"));
	m_UniformLocations[name] = location;
	return location;

}
