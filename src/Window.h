#pragma once

#include "stdio.h"

#include <GL\glew.h>
#include <GLFW\glfw3.h>

class Window
{
private:
	GLFWwindow* m_Window;

	GLint m_Width, m_Height;
	GLint bufferWidth, bufferHeight;
public:
	Window();

	Window(GLint windowWidth, GLint windowHeight);

	int Initialise();

	GLint GetBufferWidth() { return bufferWidth; }
	GLint GetBufferHeight() { return bufferHeight; }

	bool GetShouldClose() { return glfwWindowShouldClose(m_Window); }

	void SwapBuffers() { glfwSwapBuffers(m_Window); }

	void PollEvents() { glfwPollEvents(); }

	~Window();


};