#ifndef OPENGLERRORHANDLER_H
#define OPENGLERRORHANDLER_H

#include "Log.h"
#include "framework.h"
#define ASSERT(X) if(!(X)) __debugbreak();
#define GLCall(X) GLErrorHandler::GLCleanError();\
	X;\
	ASSERT(GLErrorHandler::GLLogCall(#X,__FILE__,__LINE__))


namespace GLErrorHandler {
	void glfwError(int id, const char* description);

	void GLCleanError();

	bool GLLogCall(const char* function, const char* file, int line);

	void GLAPIENTRY MessageCallback(GLenum source,
		GLenum type,
		GLuint id,
		GLenum severity,
		GLsizei length,
		const GLchar* message,
		const void* userParam);

}
#endif // OPENGLERRORHANDLER_H