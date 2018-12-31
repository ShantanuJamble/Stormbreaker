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
		std::cout << "[OpenGL Error] (" << error << ") " << function << " " << file << " " << line << std::endl;
		res = false;
	}
	return res;
}