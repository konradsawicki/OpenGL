#include "CameraController.h"
#include "Application.h"
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/glm.hpp"
#include <glm/gtx/transform.hpp>

namespace yon {
  CameraController::CameraController(float aspectRatio, const glm::vec3 &eyePos, const glm::vec3 &viewDir,
    const glm::vec3 &upDir, float FOVy, float near, float far)
    : m_camera(eyePos, viewDir, upDir, FOVy, near, far, aspectRatio) {
  }

void CameraController::OnUpdate(float deltaTime) {
  Translate(deltaTime);
  Rotate(deltaTime);
}

void CameraController::Translate(float deltaTime) {
  auto window = Application::Get()->GetMainWindow().GetNativeWindow();

  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
    auto eye = m_camera.GetEyePos();
    eye += m_camera.GetViewDir() * m_translationSpeed * deltaTime;
    m_camera.SetEyePos(eye);
  }
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
    auto eye = m_camera.GetEyePos();
    eye -= m_camera.GetViewDir() * m_translationSpeed * deltaTime;
    m_camera.SetEyePos(eye);
  }
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
    auto eye = m_camera.GetEyePos();
    auto rightDir = glm::cross(m_camera.GetViewDir(), m_camera.GetUpDir());
    eye -= rightDir * m_translationSpeed * deltaTime;
    m_camera.SetEyePos(eye);
  }
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
    auto eye = m_camera.GetEyePos();
    auto rightDir = glm::cross(m_camera.GetViewDir(), m_camera.GetUpDir());
    eye += rightDir * m_translationSpeed * deltaTime;
    m_camera.SetEyePos(eye);
  }
}

void CameraController::Rotate(float deltaTime) {
  auto window = Application::Get()->GetMainWindow().GetNativeWindow();

  int width, height;
  glfwGetWindowSize(window, &width, &height);

  double xpos, ypos;
  glfwGetCursorPos(window, &xpos, &ypos);
  glfwSetCursorPos(window, (double)width / 2.0, (double)height / 2.0);

  float deltaX = ((float)width / 2.0f) - (float)xpos;
  float deltaY = ((float)height / 2.0f) - (float)ypos;

  auto rightDir = glm::cross(m_camera.GetViewDir(), m_camera.GetUpDir());
  glm::mat3 rotator =
    glm::rotate(deltaX * m_rotationSpeed * deltaTime, -m_camera.GetUpDir()) *
    glm::rotate(deltaY * m_rotationSpeed * deltaTime, -rightDir);

  m_camera.SetViewDir(rotator * m_camera.GetViewDir());
}

}
