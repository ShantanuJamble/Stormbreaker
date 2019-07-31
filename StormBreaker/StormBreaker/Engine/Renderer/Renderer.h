#pragma once
#include <glad\glad.h>
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include <vector>

#define ASSERT(X) if(!(X)) __debugbreak();

class Renderer
{
public:
	void Clear() const;
	void Draw(VertexArray &va, IndexBuffer &ib, Shader &shader) const;
	void EnableFetures(unsigned int feature);
};