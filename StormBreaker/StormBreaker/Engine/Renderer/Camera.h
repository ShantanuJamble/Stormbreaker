#ifndef CAMERA_H
#define CAMERA_H


#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include "framework.h"
#include "Events/Event.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"

class Camera
{
private:
	glm::vec3 m_Position;
	glm::vec3 m_Front;
	glm::vec3 m_Up;
	glm::vec3 m_Right;
	glm::vec3 m_WorldUp;

	float m_Yaw;
	float m_Pitch;
	float m_lastX;
	float m_lastY;
	float m_isFirstMove;

	float m_MoveSpeed;
	float m_TurnSpeed;

	void UpdateCameraVectors();

public:
	Camera();
	Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed);

	void OnUpdate(float dt);

	void OnEvent(engine::Event &e);
	bool OnMouseMove(engine::MouseMovedEvent& e);
	bool OnMouseScroll(engine::MouseScrolledEvent& e);

	glm::mat4 CalculateViewMatrix();
	const glm::vec3& GetPostion() const { return m_Position; };
	~Camera();


};

#endif // ! CAMERA_H
