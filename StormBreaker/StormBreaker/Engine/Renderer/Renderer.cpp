#include"Renderer.h"
#include <iostream>
#include "Renderer/OpenGLErrorHandler.h"
#include "Log.h"




void Renderer::Clear() const
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glClearColor(100, 149, 237, 0.7);
}




void Renderer::Draw(VertexArray const & va, IndexBuffer const & ib, Shader const & shader) const
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
