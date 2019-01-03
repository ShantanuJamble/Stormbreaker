#pragma once
#include <GL/glew.h>
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

#define ASSERT(X) if(!(X)) __debugbreak();
#define GLCall(X) GLCleanError();\
	X;\
	ASSERT(GLLogCall(#X,__FILE__,__LINE__))


void GLCleanError();
bool GLLogCall(const char * function, const char *file, int line);

class Renderer
{
public:
	void Clear() const;
	void Draw(VertexArray &va, IndexBuffer &ib, Shader &shader) const;
};