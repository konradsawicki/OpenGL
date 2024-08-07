#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

namespace yon {

Camera::Camera(const glm::vec3& eyePos, const glm::vec3& viewDir, const glm::vec3& upDir,
  float FOVy, float near, float far, float aspectRatio)
	: m_eyePos(eyePos), m_viewDir(viewDir), m_upDir(upDir),
	  m_FOVy(FOVy), m_aspectRatio(aspectRatio), m_near(near), m_far(far) {
}

glm::mat4 Camera::GetProjectionMatrix() const {
	return glm::perspective(glm::radians(m_FOVy), m_aspectRatio, m_near, m_far);
}

glm::mat4 Camera::GetViewMatrix() const {
	return glm::lookAt(m_eyePos, m_eyePos + m_viewDir, m_upDir);
}

}
