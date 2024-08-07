#ifndef CAMERA_H
#define CAMERA_H

#include "glm/glm.hpp"

namespace yon {

class Camera
{
public:
	Camera(const glm::vec3& eyePos, const glm::vec3& viewDir, const glm::vec3& upDir,
    float FOVy, float near, float far, float aspectRatio);

public:
  void SetFOV(float FOVy) { m_FOVy = FOVy; }
  void SetAspectRatio(float aspectRatio) { m_aspectRatio = aspectRatio; }
  void SetNear(float near) { m_near = near; }
  void SetFar(float far) { m_far = far; }

  void SetEyePos(const glm::vec3& eyePos) { m_eyePos = eyePos; }
  void SetViewDir(const glm::vec3& viewDir) { m_viewDir = viewDir; }
  void SetUpDir(const glm::vec3& upDir) { m_upDir = upDir; }

  const glm::vec3& GetEyePos() const { return m_eyePos; }
  const glm::vec3& GetViewDir() const { return m_viewDir; }
  const glm::vec3& GetUpDir() const { return m_upDir; }

	glm::mat4 GetProjectionMatrix() const; // View space to Clip space
	glm::mat4 GetViewMatrix() const; // World space to View space
	// Clip space To NDC is done by OpenGL (division of vertices' positions by w)

private:
	glm::vec3 m_eyePos;
	glm::vec3 m_viewDir;
	glm::vec3 m_upDir;

	float m_FOVy;
	float m_aspectRatio;
	float m_near;
	float m_far;
};

}

#endif