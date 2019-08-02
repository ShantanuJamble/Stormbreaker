#ifndef RENDERER_H
#define RENDERER_H
#include "framework.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include <vector>
#include "Renderer/OpenGLErrorHandler.h"


class Renderer
{
public:
	void Clear() const;
	void Draw(VertexArray const &va, IndexBuffer const &ib, Shader const &shader) const;
	void EnableFetures(unsigned int feature);
};

#endif