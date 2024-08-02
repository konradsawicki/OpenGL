#ifndef GRAPHICSCONTEXT_H
#define GRAPHICSCONTEXT_H

class GLFWwindow;
namespace yon {

class GraphicsContext {
public:
  void Create(GLFWwindow* window);
  void SwapBuffers();

private:
  GLFWwindow* m_handle = nullptr;
};



}




#endif