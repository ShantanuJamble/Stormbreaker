#include"Renderer.h"
#include <iostream>
#include "Renderer/OpenGLErrorHandler.h"
#include "Log.h"
#include "SkyboxTexture.h"




void Renderer::Clear() const
{
	//Cornflower blue
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
}




void Renderer::Draw(VertexArray const & va, IndexBuffer const & ib, Shader const & shader) const
{
	shader.UseShader();
	va.Bind();
	ib.Bind();

	glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
	
}

void Renderer::DrawSky(VertexArray const& va, IndexBuffer const& ib, Shader const& shader) const
{
	glDepthMask(GL_FALSE); // TODO: we need renderpasses!!!!!!! this is not maintainable!!
	shader.UseShader();
	va.Bind();
	ib.Bind();
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glDepthMask(GL_TRUE);
}

void Renderer::EnableFetures(unsigned int feature)
{
	glEnable(feature);
}
