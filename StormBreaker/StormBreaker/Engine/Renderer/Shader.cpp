#include "Shader.h"
#include "Log.h"
#include <glm/gtc/type_ptr.hpp>

/**
* Get vertex/fragment code from the file path\
*/
void Shader::LoadShaderCode(const GLchar* filePath, GLenum& type)
{
	std::string shaderSrc;
	std::ifstream shaderFile;
	shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		//Open the files
		shaderFile.open(filePath);
		//Read file's buffer content into the streams
		std::stringstream shaderSrcStream;
		shaderSrcStream << shaderFile.rdbuf();
		
		//Close the files
		shaderFile.close();

		switch (type)
		{
		case GL_VERTEX_SHADER:
			m_vertexShader.m_source = shaderSrcStream.str();
		case GL_FRAGMENT_SHADER:
			m_fragmentShader.m_source = shaderSrcStream.str();
		}
	}
	catch (std::exception e)
	{
		SB_ENGINE_ERROR("ERROR::Failed to read shader code.{0} at {1} from {2}",
											e.what(),__FUNCTION__, std::string(filePath).c_str());
	}
}





/**
* Compiles the shader code recieved from load shader function to store an id for the compiled source code.
*/
void Shader::CompileShaderCode(SimpleShader& shader)
{
	
	shader.m_shaderId = glCreateShader(shader.m_type); //generate the shader buffer

	const char* src = shader.m_source.c_str();	// converts to const char*
	glShaderSource(shader.m_shaderId, 1, &src, NULL);//binds source to shader id
	glCompileShader(shader.m_shaderId);//compilder the shader with provided id
	
	//Print any compilation errors
	int success;
	char infoLog[512];
	glGetShaderiv(shader.m_shaderId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader.m_shaderId, 512, NULL, infoLog);
		SB_ENGINE_ERROR("Error::Shader compilation failed:\n {0}", infoLog);
	};
}


/**
* Links the shaders with current program.
*/

void Shader::LinkShaders()
{
	//Link Shaders
	m_programID = glCreateProgram();
	glAttachShader(m_programID, m_vertexShader.m_shaderId);
	glAttachShader(m_programID, m_fragmentShader.m_shaderId);
	glLinkProgram(m_programID);
	glValidateProgram(m_programID);
	//Print any linking errors
	int success;
	char infoLog[512];
	glGetProgramiv(m_programID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(m_programID, 512, NULL, infoLog);
		SB_ENGINE_ERROR("Error::Shader Linking Failed {0}", infoLog);
	}
}


/*
* Shader constructor takes in paths to the src files of shaders and takes care of building and linking them with the 
* current opengl context.
* Parameters must be in order of VertexShaderPath, Fragmentshaderpath
*/
Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath)
	:m_vertexShader(GL_VERTEX_SHADER),
	 m_fragmentShader(GL_FRAGMENT_SHADER)
{	
	//Read the shaders 
	GLenum vertexShader = GL_VERTEX_SHADER;
	LoadShaderCode(vertexPath, vertexShader);
	GLenum fragmentShader = GL_FRAGMENT_SHADER;
	LoadShaderCode(fragmentPath, fragmentShader);

	//Compile the shaders
	CompileShaderCode(m_vertexShader);
	CompileShaderCode(m_fragmentShader);

	//Link Shaders
	LinkShaders();

	SB_ENGINE_INFO("INFO: Shaders compiled and linked.");

	//Delete the Shaders after they're linked to the program
	glDeleteShader(m_vertexShader.m_shaderId);
	glDeleteShader(m_fragmentShader.m_shaderId);
}



void Shader::UseShader() const
{
	GLCall(glUseProgram(m_programID));
}



/************************************************************************************

					Shader Uniform setup methods

************************************************************************************/

int Shader::GetUniformLocation(const std::string& name) const
{
	int location;
	if (m_UniformLocations.find(name) != m_UniformLocations.end())
		return m_UniformLocations[name];
	else
		location = glGetUniformLocation(this->m_programID , name.c_str());
	m_UniformLocations[name] = location;
	SB_ENGINE_INFO("INFO: {0} : {1}", name, location);
	return location;

}


int Shader::GetUniformBufferIndex(const std::string& name ) const
{
	int location;
	if (m_UniformLocations.find(name) != m_UniformLocations.end())
		return m_UniformLocations[name];
	else
		location = glGetUniformBlockIndex(this->m_programID, name.c_str());
	m_UniformLocations[name] = location;
	SB_ENGINE_INFO("INFO: {0} : {1}", name, location);
	return location;
}


void Shader::SetBool(const std::string& name, bool value) const
{
	glUniform1i(GetUniformLocation(name), (int)value);
}

void Shader::SetInt(const std::string& name, int value) const
{
	glUniform1i(GetUniformLocation(name), value);
}

void Shader::SetFloat(const std::string& name, float value) const
{
	glUniform1f(GetUniformLocation(name), value);
}

void Shader::SetFloat4(const std::string& name, float r, float g, float b, float a)
{
	glUniform4f(GetUniformLocation(name), r, g, b, a);
}

void Shader::SetVec2(const std::string& name, const glm::vec2& value) const
{
	glUniform2fv(GetUniformLocation(name), 1, &value[0]);
}

void Shader::SetVec2(const std::string& name, float x, float y) const
{
	glUniform2f(GetUniformLocation(name), x, y);
}

void Shader::SetVec3(const std::string& name, const glm::vec3& value) const
{
	glUniform3fv(GetUniformLocation(name), 1, &value[0]);
}

void Shader::SetVec3(const std::string& name, float x, float y, float z) const
{
	glUniform3f(GetUniformLocation(name), x, y, z);
}

void Shader::SetVec4(const std::string& name, const glm::vec4& value) const
{
	glUniform4fv(GetUniformLocation(name), 1, &value[0]);
}

void Shader::SetVec4(const std::string& name, float x, float y, float z, float w) const
{
	glUniform4f(GetUniformLocation(name), x, y, z, w);
}

void Shader::SetMat2(const std::string& name, const glm::mat2& mat) const
{
	glUniformMatrix2fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(mat));
}

void Shader::SetMat3(const std::string& name, const glm::mat3& mat) const
{
	glUniformMatrix3fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(mat));
}

void Shader::SetMat4(const std::string& name, const glm::mat4& mat) const
{
	glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(mat));
}

void Shader::SetUniformBlock(const std::string& name, const unsigned int slot /*=0*/)
{
	SB_ENGINE_INFO("Setting up {0},{1}.{2}", name.c_str(), slot, GetUniformBufferIndex(name));
	glUniformBlockBinding(m_programID, GetUniformBufferIndex(name), slot);
}

