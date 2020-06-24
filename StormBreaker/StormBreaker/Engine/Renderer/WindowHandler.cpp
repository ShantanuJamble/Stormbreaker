#include "WindowHandler.h"
#include "Log.h"
#include "OpenGLErrorHandler.h"

namespace Engine {
	Window::Window()
	{
		m_Width = 800;
		m_Height = 600;
		m_deltaTime = 0.0f;
		m_lastTime = 0.0f;
		for (size_t i = 0; i < 1024; i++)
			m_keys[i] = 0;

		//Setting up openGL error handler
		glfwSetErrorCallback(&GLErrorHandler::glfwError);
	}

	Window::Window(GLint windowWidth, GLint windowHeight, const EventCallbackFn& callback)
	{
		m_Width = windowWidth;
		m_Height = windowHeight;
		m_callback = callback;
		m_deltaTime = 0.0f;
		m_lastTime = 0.0f;
		for (size_t i = 0; i < 1024; i++)
			m_keys[i] = 0;

		//Setting up openGL error handler
		glfwSetErrorCallback(&GLErrorHandler::glfwError);
	}

	Window::Window(GLint windowWidth, GLint windowHeight)
	{
		m_Width = windowWidth;
		m_Height = windowHeight;
		m_deltaTime = 0.0f;
		m_lastTime = 0.0f;
		for (size_t i = 0; i < 1024; i++)
			m_keys[i] = 0;

		//Setting up openGL error handler
		glfwSetErrorCallback(&GLErrorHandler::glfwError);
	}


	int Window::Initialise()
	{
		if (!glfwInit())
		{
			printf("Error Initializing GLFW");
			glfwTerminate();
			return 1;
		}

		// Setup GLFW Windows Properties
		// OpenGL version
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		// Core Profile
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		// Allow forward compatibility
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

		// Create the window
		m_Window = glfwCreateWindow(m_Width, m_Height, "Test Window", NULL, NULL);
		if (!m_Window)
		{
			printf("Error creating GLFW window!");
			glfwTerminate();
			return 1;
		}

		// Get buffer size information
		glfwGetFramebufferSize(m_Window, &m_BufferWidth, &m_BufferHeight);

		// Set the current context
		glfwMakeContextCurrent(m_Window);
		//enable vsync
		glfwSwapInterval(1);


		//Handle Input
		CreateCallback();
		glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

		// Allow modern extension access
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

		if (!status)
			SB_ENGINE_ERROR("ERROR: Failed to load glad.");

		glEnable(GL_DEPTH_TEST);//Want this to be default thing. Renderer methods can later on be used to change.
		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(GLErrorHandler::MessageCallback, nullptr);

		// Create Viewport
		glViewport(0, 0, m_BufferWidth, m_BufferHeight);


		//Setting pointer to call static methods from callback
		glfwSetWindowUserPointer(m_Window, this);
		return 0;
	}


	Window::~Window()
	{
		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}

	void Window::CreateCallback()
	{
		glfwSetKeyCallback(m_Window, KeyHandler);
		/*glfwSetCursorPosCallback(m_Window, MouseHandler);*/
		// Set GLFW callbacks
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
			Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
			
			WindowResizeEvent event(width, height);
			(theWindow->GetEventCallback())(event);
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
		{
			Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
			WindowCloseEvent event;
			(theWindow->GetEventCallback())(event);

		});

	/*	glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			
		});*/

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)
		{
			Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

			KeyTypedEvent event(static_cast<uint16_t>(keycode));
			(theWindow->GetEventCallback())(event);
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
		{
			Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

			switch (action)
			{
			case GLFW_PRESS:
			{
				MouseButtonPressedEvent event(static_cast<uint16_t>(button));
				(theWindow->GetEventCallback())(event);
				break;
			}
			case GLFW_RELEASE:
			{
				MouseButtonReleasedEvent event(static_cast<uint16_t>(button));
				(theWindow->GetEventCallback())(event);
				break;
			}
			}
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

			MouseScrolledEvent event((float)xOffset, (float)yOffset);
			(theWindow->GetEventCallback())(event);
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
		{
			Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

			MouseMovedEvent event((float)xPos, (float)yPos);
			(theWindow->GetEventCallback())(event);
		});
	}

	void Window::KeyHandler(GLFWwindow* window, int key, int code, int action, int mode)
	{
		Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

		switch (action)
		{
		case GLFW_PRESS:
		{
			KeyPressedEvent event(static_cast<uint16_t>(key), 0);
			(theWindow->GetEventCallback())(event);
			break;
		}
		case GLFW_RELEASE:
		{
			KeyReleasedEvent event(static_cast<uint16_t>(key));
			(theWindow->GetEventCallback())(event);
			break;
		}
		case GLFW_REPEAT:
		{
			KeyPressedEvent event(static_cast<uint16_t>(key), 1);
			(theWindow->GetEventCallback())(event);
			break;
		}
		}

	}



	void Window::MouseHandler(GLFWwindow* window, double xPos, double yPos)
	{
		Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
		GLfloat tmpXpos = (GLfloat)xPos;
		GLfloat tmpYpos = (GLfloat)yPos;
		if (theWindow->m_mouseFirstmoved)
		{
			theWindow->m_mouseFirstmoved = false;
			theWindow->m_lastX = tmpXpos;
			theWindow->m_lastY = tmpYpos;
		}
		else
		{
			theWindow->m_xchanged = tmpXpos - theWindow->m_lastX;
			theWindow->m_ychanged = theWindow->m_lastY - tmpYpos;
			theWindow->m_lastX = tmpXpos;
			theWindow->m_lastY = tmpYpos;
		}
	}


	GLfloat Window::GetXchanged()
	{
		GLfloat change = m_xchanged;
		m_xchanged = 0.0f;
		return change;
	}

	GLfloat Window::GetYchanged()
	{
		GLfloat change = m_ychanged;
		m_ychanged = 0.0f;
		return change;
	}

	GLfloat Window::GetTimeDelta()
	{
		GLfloat now = (GLfloat)glfwGetTime(); // SDL_GetPerformanceCounter();
		m_deltaTime = now - m_lastTime; // (now - lastTime)*1000/SDL_GetPerformanceFrequency();
		m_lastTime = now;

		return m_deltaTime;
	}

	void Window::OnViewPortResize(float width, float height)
	{
		m_BufferWidth = width;
		m_BufferHeight = height;
		glViewport(0, 0, m_BufferWidth, m_BufferHeight);
	}
}