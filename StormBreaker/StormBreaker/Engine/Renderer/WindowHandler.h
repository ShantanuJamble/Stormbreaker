#ifndef WINDOWHANDLER_H
#define WINDOWHANDLER_H

#include "stdio.h"

#include <glad/glad.h>
#include <GLFW\glfw3.h>
#include <Events/Event.h>
#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"
namespace engine {

	using EventCallbackFn = std::function<void(Event&)>;
	class Window
	{
	private:
		GLFWwindow* m_Window;

		GLint m_Width, m_Height;
		GLint m_BufferWidth, m_BufferHeight;

		//Key Handling
		bool m_keys[1024];
		EventCallbackFn m_callback;
		//Mouse Handling
		GLfloat m_lastX;
		GLfloat m_lastY;
		GLfloat m_xchanged;
		GLfloat m_ychanged;
		bool m_mouseFirstmoved;

		GLfloat m_deltaTime;
		GLfloat m_lastTime;
	public:
		Window(const char* windowTitle);

		Window(const char* windowTitle,GLint windowWidth, GLint windowHeight);
		Window(const char* windowTitle,GLint windowWidth, GLint windowHeight, const EventCallbackFn& callback);

		int Initialise(const char* windowTitle);

		inline GLint GetBufferWidth()  const { return m_BufferWidth; }
		inline GLint GetBufferHeight() const { return m_BufferHeight; }

		inline bool GetWindowShouldClose() const { return glfwWindowShouldClose(m_Window); }

		inline void SwapBuffers() const { glfwSwapBuffers(m_Window); }

		inline void PollEvents() const { glfwPollEvents(); }

		~Window();

		void CreateCallback();

		void SetEventCallback(const EventCallbackFn& callback) { m_callback = callback; }

		const EventCallbackFn& GetEventCallback() const { return m_callback; }
		//Key hit callback
		static void KeyHandler(GLFWwindow* window, int key, int code, int action, int mode);
		//Mouse Handler
		static void MouseHandler(GLFWwindow* window, double xPos, double yPos);
		void OnViewPortResize(float width, float height);
		bool* GetKeys() { return m_keys; };
		inline bool isKeyDown(int code) const { return m_keys[code]; }
		GLfloat GetXchanged();
		GLfloat GetYchanged();
		GLfloat GetTimeDelta();
		
		GLFWwindow* GetGLFWWindow() const { return m_Window; }

	};
}

#endif //WINDOWHANDLER_H