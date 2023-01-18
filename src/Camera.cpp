#include "Camera.h"
#include "Renderer.h"
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/transform.hpp"
#include "GLFW/glfw3.h"

Camera::Camera(float FOVy, float AspectRatio, float NearPlanePosition, float FarPlanePosition)
	: m_Position(0.f, 0.f, 0.f), m_ViewDirection(0.f, 0.f, -1.f), 
	  m_UpVector(0.f, 1.f, 0.f), m_OldMousePos(640.f, 360.f),
	  m_FieldOfView_Y(FOVy), m_AspectRatio(AspectRatio),
	  m_NearPlanePosition(NearPlanePosition), m_FarPlanePosition(FarPlanePosition)
{
	m_RightVector = glm::cross(m_ViewDirection, m_UpVector);
}

void Camera::SetFieldOfView(float FOVy)
{
	m_FieldOfView_Y = FOVy;
}

void Camera::SetAspectRatio(float AspectRatio)
{
	m_AspectRatio = AspectRatio;
}

void Camera::SetNearPlanePosition(float NearPlanePosition)
{
	m_NearPlanePosition = NearPlanePosition;
}

void Camera::SetFarPlanePosition(float FarPlanePosition)
{
	m_FarPlanePosition = FarPlanePosition;
}

glm::mat4 Camera::GetProjectionMatrix() const
{
	return glm::perspective(glm::radians(m_FieldOfView_Y), m_AspectRatio, m_NearPlanePosition, m_FarPlanePosition);
}

glm::mat4 Camera::GetViewMatrix() const
{
	return glm::lookAt(m_Position, m_Position + m_ViewDirection, m_UpVector);
}

void Camera::Rotate(glm::vec2 NewMousePos)
{
	glm::vec2 MouseDelta = NewMousePos - m_OldMousePos;
	const float rotation_speed = 0.002f;
	m_RightVector = glm::cross(m_ViewDirection, m_UpVector);
	glm::mat4 Rotator = glm::rotate(MouseDelta.x * rotation_speed, - m_UpVector) *
						glm::rotate(MouseDelta.y * rotation_speed, - m_RightVector);

	m_ViewDirection = glm::mat3(Rotator) * m_ViewDirection;

	m_OldMousePos = NewMousePos;
}

void Camera::Translate(int key)
{
	float translation_speed = 0.1f;
	switch (key)
	{
		case GLFW_KEY_W: m_Position += m_ViewDirection * translation_speed; break;
		case GLFW_KEY_S: m_Position -= m_ViewDirection * translation_speed; break;
		case GLFW_KEY_A: m_Position -= m_RightVector * translation_speed; break;
		case GLFW_KEY_D: m_Position += m_RightVector * translation_speed; break;
		default: break;
	}
}
