#include"Renderer.h"
#include <iostream>

void GLCleanError()
{
	while (glGetError());
}

bool GLLogCall(const char * function, const char *file, int line)
{
	bool res = true;
	GLenum error;
	while (error = glGetError()) {
		std::cout << "[OpenGL Error] (" << error << ") "<< std::endl;
		std::cout<< function << " " << file << " " << line << std::endl;
		res = false;
	}
	return res;
}

void Renderer::Clear() const
{
	
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}

void Renderer::Draw(VertexArray & va, IndexBuffer & ib, Shader & shader) const
{
	shader.UseShader();
	va.Bind();
	ib.Bind();
	glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::EnableFetures(unsigned int feature)
{
	glEnable(feature);
}
