#ifndef CAMERACONTROLLER_H
#define CAMERACONTROLLER_H

#include "Camera.h"

namespace yon {

class CameraController {
public:
  CameraController(float aspectRatio, const glm::vec3& eyePos = {0.f, 0.f, 0.f},
    const glm::vec3& viewDir = {0.f, 0.f, -1.f}, const glm::vec3& upDir = {0.f, 1.f, 0.f},
    float FOVy = 90.f, float near = 0.01f, float far = 1000.f);

  void OnUpdate(float deltaTime);

  const Camera& GetCamera() const { return m_camera; }

private:
  void Translate(float deltaTime);
  void Rotate(float deltaTime);

private:
  Camera m_camera;
  float m_translationSpeed = 5.f;
  float m_rotationSpeed = 0.5f;
};

}


#endif
