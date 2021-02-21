#include "Camera.h"
#include <iostream>

#include "Core/Input.h"

Camera::Camera() {}

Camera::Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed)
{
	m_Position = startPosition;
	m_WorldUp = startUp;
	m_Yaw = startYaw;
	m_Pitch = startPitch;
	m_Front = glm::vec3(0.0f, 0.0f, -1.0f);

	m_MoveSpeed = startMoveSpeed;
	m_TurnSpeed = startTurnSpeed;
	m_isFirstMove = true;

	UpdateCameraVectors();
	
}


void Camera::OnEvent(engine::Event& e)
{
	engine::EventDispatcher dispatcher(e);
	dispatcher.Dispatch<engine::MouseScrolledEvent>(SB_BIND_EVENT_FN(Camera::OnMouseScroll));
	dispatcher.Dispatch<engine::MouseMovedEvent>(SB_BIND_EVENT_FN(Camera::OnMouseMove));
}


bool Camera::OnMouseMove(engine::MouseMovedEvent& e)
{
	if (m_isFirstMove)
	{
		m_lastX = e.GetX();
		m_lastY = e.GetY();
		m_isFirstMove = false;
		return true;
	}
	else {
		float xChange = e.GetX() - m_lastX;
		float yChange = m_lastY - e.GetY();

		m_lastX = e.GetX();
		m_lastY = e.GetY();

		xChange *= m_TurnSpeed;
		yChange *= m_TurnSpeed;

		m_Yaw += xChange;
		m_Pitch += yChange;

		if (m_Pitch > 89.0f)
		{
			m_Pitch = 89.0f;
		}

		if (m_Pitch < -89.0f)
		{
			m_Pitch = -89.0f;
		}


	}
	UpdateCameraVectors();

	return true;
}


bool Camera::OnMouseScroll(engine::MouseScrolledEvent& e)
{

	/*if (offset == 0) return;
	
	if (m_Zoom >= 1.0f && m_Zoom <= 45.0f)
		m_Zoom -= yoffset;
	else if (m_Zoom <= 1.0f)
		m_Zoom = 1.0f;
	else if (m_Zoom >= 45.0f)
		m_Zoom = 45.0f;
	*/return false;
}

glm::mat4  Camera::CalculateViewMatrix()
{
	glm::mat4 View = glm::lookAt(m_Position, m_Position + m_Front, m_Up);
	return View;
}

void Camera::OnUpdate(float dt)
{
	GLfloat velocity = m_MoveSpeed * dt;
	float isDirty = false;
	if (INPUT::IsKeyPressed(GLFW_KEY_W))
	{
		m_Position += m_Front * velocity;
		isDirty = true;
	}

	if (INPUT::IsKeyPressed(GLFW_KEY_S))
	{
		m_Position -= m_Front * velocity;
		isDirty = true;
	}

	if (INPUT::IsKeyPressed(GLFW_KEY_A))
	{
		m_Position -= m_Right * velocity;
		isDirty = true;
	}

	if (INPUT::IsKeyPressed(GLFW_KEY_D))
	{
		m_Position += m_Right * velocity;
		isDirty = true;
	}

	if (isDirty)
		UpdateCameraVectors();

	
}

void Camera::UpdateCameraVectors()
{
	m_Front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
	m_Front.y = sin(glm::radians(m_Pitch));
	m_Front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
	m_Front = glm::normalize(m_Front);

	m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
	m_Up = glm::normalize(glm::cross(m_Right, m_Front));

}
Camera::~Camera()
{
}
