#ifndef CAMERA_H
#define CAMERA_H


#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include "framework.h"

class Camera
{
private:
	glm::vec3 m_Position;
	glm::vec3 m_Front;
	glm::vec3 m_Up;
	glm::vec3 m_Right;
	glm::vec3 m_WorldUp;

	GLfloat m_Yaw;
	GLfloat m_Pitch;

	GLfloat m_MoveSpeed;
	GLfloat m_TurnSpeed;

	void Update();

public:
	Camera();
	Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed);

	void KeyControl(bool* keys, GLfloat deltaTime);
	void MouseControl(GLfloat xChange, GLfloat yChange);

	 glm::mat4 CalculateViewMatrix();

	~Camera();


};

#endif // ! CAMERA_H
