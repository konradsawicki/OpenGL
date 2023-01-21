#include "Camera.h"
#include "Renderer.h"
#include "glm/gtx/transform.hpp"
#include "GLFW/glfw3.h"

Camera::Camera(glm::vec2 FOV, float AspectRatio, float NearPlanePosition, float FarPlanePosition)
	: m_Position(0.f, 0.f, 0.f), m_ViewDirection(0.f, 0.f, -1.f), 
	  m_UpVector(0.f, 1.f, 0.f), m_OldMousePos(0.f, 0.f),
	  m_FieldOfView(FOV), m_AspectRatio(AspectRatio),
	  m_NearPlanePosition(NearPlanePosition), m_FarPlanePosition(FarPlanePosition)
{
}

void Camera::SetFieldOfView(glm::vec2 FOV)
{
	m_FieldOfView = FOV;
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
	return glm::perspective(glm::radians(m_FieldOfView.y), m_AspectRatio, m_NearPlanePosition, m_FarPlanePosition);
}

glm::mat4 Camera::GetWorldToViewMatrix() const
{
	return glm::lookAt(m_Position, m_Position + m_ViewDirection, m_UpVector);
}

void Camera::UpdateMousePosition(glm::vec2 NewMousePos)
{
	glm::vec2 MouseDelta = NewMousePos - m_OldMousePos;
	m_ViewDirection = glm::mat3(glm::rotate(MouseDelta.x * 0.01f, m_UpVector)) * m_ViewDirection;
	m_OldMousePos = NewMousePos;
}
