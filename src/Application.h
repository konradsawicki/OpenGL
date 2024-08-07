#ifndef APPLICATION_H
#define APPLICATION_H

#include "Window.h"
#include "CameraController.h"

namespace yon {

class Application {
public:
  Application();
  void Run();

  const Window& GetMainWindow() const { return m_window; }

  static Application& Get() { return *m_app; }

private:
  void OnEvent(IEvent& event);
private:
  inline static Application* m_app;

  Window m_window;
  CameraController m_cameraControl;

  bool m_running = true;
};

}

#endif