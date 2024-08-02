#include "GraphicsContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Core.h"

namespace yon {

void GraphicsContext::Create(GLFWwindow *window) {
  m_handle = window;
  glfwMakeContextCurrent(m_handle);
  auto success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
  ASSERT(success);
}

void GraphicsContext::SwapBuffers() {
  glfwSwapBuffers(m_handle);
}

}