#include "Camera.h"
#include "Renderer.h"
#include "glm/gtx/transform.hpp"
#include "GLFW/glfw3.h"

Camera::Camera(float FOVy, float AspectRatio, float NearPlanePosition, float FarPlanePosition)
	: m_Position(0.f, 0.f, 0.f), m_ViewDirection(0.f, 0.f, -1.f), 
	  m_UpVector(0.f, 1.f, 0.f), m_OldMousePos(0.f, 0.f),
	  m_FieldOfView_Y(FOVy), m_AspectRatio(AspectRatio),
	  m_NearPlanePosition(NearPlanePosition), m_FarPlanePosition(FarPlanePosition)
{
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

void Camera::Update(glm::vec2 NewMousePos)
{
	glm::vec2 MouseDelta = NewMousePos - m_OldMousePos;
	const float rotational_speed = 0.002f;
	glm::vec3 RightVector = glm::cross(m_ViewDirection, m_UpVector);
	glm::mat4 Rotator = glm::rotate(MouseDelta.x * rotational_speed, m_UpVector) *
						glm::rotate(MouseDelta.y * rotational_speed, RightVector);

	m_ViewDirection = glm::mat3(Rotator) * m_ViewDirection;

	m_OldMousePos = NewMousePos;
}
