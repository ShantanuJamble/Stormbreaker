#include "Input.h"
namespace engine {

	bool Input::IsKeyPressed(int32_t keyCode)
	{
		auto window = static_cast<GLFWwindow*>(Application::GetInstance().GetWindow().GetGLFWWindow());
		auto state = glfwGetKey(window, keyCode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool Input::IsKeyRelesed(int32_t keyCode)
	{
		auto window = static_cast<GLFWwindow*>(Application::GetInstance().GetWindow().GetGLFWWindow());
		auto state = glfwGetKey(window, keyCode);
		return state == GLFW_RELEASE;
	}


	bool Input::IsMouseButtonPressed(int32_t button)
	{
		auto window = static_cast<GLFWwindow*>(Application::GetInstance().GetWindow().GetGLFWWindow());
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	std::pair<float, float> Input::GetMousePosition()
	{
		auto window = static_cast<GLFWwindow*>(Application::GetInstance().GetWindow().GetGLFWWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		return { (float)xpos, (float)ypos };
	}

	float Input::GetMouseX()
	{
		auto [x, y] = GetMousePosition();
		return x;
	}

	float Input::GetMouseY()
	{
		auto [x, y] = GetMousePosition();
		return x;			
	}
}