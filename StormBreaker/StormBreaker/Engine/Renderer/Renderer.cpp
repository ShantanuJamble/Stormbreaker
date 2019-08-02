#include"Renderer.h"
#include <iostream>
#include "Renderer/OpenGLErrorHandler.h"
#include "Log.h"




void Renderer::Clear() const
{
	glClearColor(0.0f, 0.5f, 0.5f, 1.0f);
	GLCall(glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT));
}




void Renderer::Draw(VertexArray const & va, IndexBuffer const & ib, Shader const & shader) const
{
	shader.UseShader();
	va.Bind();
	ib.Bind();

	GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
	
}

void Renderer::EnableFetures(unsigned int feature)
{
	GLCall(glEnable(feature));
}
