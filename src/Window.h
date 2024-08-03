#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>
#include <string>
#include <functional>

#include "GraphicsContext.h"
#include "Event.h"

namespace yon {

class Window {
public:
  virtual ~Window();
  void Create(int width, int height, std::string title);

  void SetCallback(std::function<void(IEvent&)> callback) { m_data.m_callback = callback; }
  void Update();

private:
  GLFWwindow* m_window;
  GraphicsContext m_context;

  struct WindowData {
    std::function<void(IEvent&)> m_callback;
  };
  WindowData m_data;
};

}

#endif