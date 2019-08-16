#ifndef WINDOWHANDLER_H
#define WINDOWHANDLER_H

#include "stdio.h"

#include <glad/glad.h>
#include <GLFW\glfw3.h>

class Window
{
private:
	GLFWwindow* m_Window;

	GLint m_Width, m_Height;
	GLint m_BufferWidth, m_BufferHeight;

	//Key Handling
	bool m_keys[1024];

	//Mouse Handling
	GLfloat m_lastX;
	GLfloat m_lastY;
	GLfloat m_xchanged;
	GLfloat m_ychanged;
	bool m_mouseFirstmoved;

	GLfloat m_deltaTime;
	GLfloat m_lastTime;
public:
	Window();

	Window(GLint windowWidth, GLint windowHeight);

	int Initialise();

	inline GLint GetBufferWidth()  const { return m_BufferWidth; }
	inline GLint GetBufferHeight() const { return m_BufferHeight; }

	inline bool GetWindowShouldClose() const { return glfwWindowShouldClose(m_Window); }

	inline void SwapBuffers() const { glfwSwapBuffers(m_Window); }

	inline void PollEvents() const { glfwPollEvents(); }

	~Window();

	void CreatCallback();
	//Key hit callback
	static void KeyHandler(GLFWwindow* window, int key, int code, int action, int mode);
	//Mouse Handler
	static void MouseHandler(GLFWwindow* window, double xPos, double yPos);

	bool* GetKeys() { return m_keys; };
	GLfloat GetXchanged();
	GLfloat GetYchanged();
	GLfloat GetTimeDelta();

	GLFWwindow* GetGLFWWindow() const { return m_Window; }

};

#endif //WINDOWHANDLER_H