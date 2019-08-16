#include "WindowHandler.h"
#include "Log.h"
#include "OpenGLErrorHandler.h"


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
	glfwSwapInterval(1.0f);


	//Handle Input
	CreatCallback();
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
}


Window::~Window()
{
	glfwDestroyWindow(m_Window);
	glfwTerminate();
}

void Window::CreatCallback()
{
	glfwSetKeyCallback(m_Window, KeyHandler);
	glfwSetCursorPosCallback(m_Window, MouseHandler);
}

void Window::KeyHandler(GLFWwindow* window, int key, int code, int action, int mode)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key <= 1024)
	{
		if (action == GLFW_PRESS)
		{
			theWindow->m_keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			theWindow->m_keys[key] = false;
		}
	}

}

void Window::MouseHandler(GLFWwindow* window, double xPos, double yPos)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (theWindow->m_mouseFirstmoved)
	{
		theWindow->m_mouseFirstmoved = false;
		theWindow->m_lastX = xPos;
		theWindow->m_lastY = yPos;
	}
	else
	{
		theWindow->m_xchanged = xPos - theWindow->m_lastX;
		theWindow->m_ychanged = theWindow->m_lastY - yPos;
		theWindow->m_lastX = xPos;
		theWindow->m_lastY = yPos;
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
	GLfloat now = glfwGetTime(); // SDL_GetPerformanceCounter();
	m_deltaTime = now - m_lastTime; // (now - lastTime)*1000/SDL_GetPerformanceFrequency();
	m_lastTime = now;

	return m_deltaTime;
}
