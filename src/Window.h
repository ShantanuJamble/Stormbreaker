#pragma once

#include "stdio.h"

#include <GL\glew.h>
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

	GLint GetBufferWidth() { return m_BufferWidth; }
	GLint GetBufferHeight() { return m_BufferHeight; }

	bool GetShouldClose() { return glfwWindowShouldClose(m_Window); }

	void SwapBuffers() { glfwSwapBuffers(m_Window); }

	void PollEvents() { glfwPollEvents(); }

	~Window();

	void CreatCallback();
	//Keyhit callback
	static void KeyHandler(GLFWwindow * window, int key, int code, int action, int mode);
	//Mouse Handler
	static void MouseHandler(GLFWwindow *  window, double xPos, double yPos);

	bool* GetKeys() { return m_keys; };
	GLfloat GetXchanged();
	GLfloat GetYchanged();
	GLfloat GetTimeDelta();

};