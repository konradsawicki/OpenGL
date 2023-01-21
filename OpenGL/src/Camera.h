#pragma once
#include "glm/glm.hpp"

class Camera
{
public:
	Camera(glm::vec2 FOV, float AspectRatio, float NearPlanePosition, float FarPlanePosition);

private:
	glm::vec3 m_Position;
	glm::vec3 m_ViewDirection;
	const glm::vec3 m_UpVector;

	glm::vec2 m_OldMousePos;

	glm::vec2 m_FieldOfView;
	float m_AspectRatio;
	float m_NearPlanePosition;
	float m_FarPlanePosition;

public:
	void SetFieldOfView(glm::vec2 FOV);
	void SetAspectRatio(float AspectRatio);
	void SetNearPlanePosition(float NearPlanePosition);
	void SetFarPlanePosition(float FarPlanePosition);

	glm::mat4 GetProjectionMatrix() const;
	glm::mat4 GetWorldToViewMatrix() const;

	void UpdateMousePosition(glm::vec2 NewMousePos);


	
};