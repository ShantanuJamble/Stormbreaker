#include "OpenGLErrorHandler.h"

void GLErrorHandler::glfwError(int id, const char* description)
{
	SB_ENGINE_ERROR("ERROR:{0}, {1}", id, description);
}

void GLErrorHandler::GLCleanError()
{
	while (glGetError());
}

bool GLErrorHandler::GLLogCall(const char* function, const char* file, int line)
{
	bool res = true;
	GLenum error;
	while (error = glGetError()) {
		SB_ENGINE_ERROR("ERROR:[OpenGL Error] ( {0} ) , {1},{2},{3}", error, function, file, line);
		res = false;
	}
	return res;
}

void GLAPIENTRY GLErrorHandler::MessageCallback(GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam)
{
	/*fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
		(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
		type, severity, message);*/

	SB_ENGINE_ERROR("GL CALLBACK: {0} type = {1}, severity = {2}, message ={3}\n",
		(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
		type, severity, message);
}