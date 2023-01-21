#pragma once
#include "glm/glm.hpp"

class Camera
{
public:
	Camera(float FOVy, float AspectRatio, float NearPlanePosition, float FarPlanePosition);

private:
	glm::vec3 m_Position;
	glm::vec3 m_ViewDirection;
	const glm::vec3 m_UpVector;
	glm::vec3 m_RightVector;
	glm::vec2 m_OldMousePos;

	float m_FieldOfView_Y;
	float m_AspectRatio;
	float m_NearPlanePosition;
	float m_FarPlanePosition;

public:
	void SetFieldOfView(float FOVy);
	void SetAspectRatio(float AspectRatio);
	void SetNearPlanePosition(float NearPlanePosition);
	void SetFarPlanePosition(float FarPlanePosition);

	
	glm::mat4 GetProjectionMatrix() const; // View space to Clip space
	glm::mat4 GetViewMatrix() const; // World space to View space
	// Clip space To NDC is done by OpenGL (division of vertices' positions by w) 
	
	void Rotate(glm::vec2 NewMousePos);
	void Translate(int key);
};