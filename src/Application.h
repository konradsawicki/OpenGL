#ifndef APPLICATION_H
#define APPLICATION_H

#include "Window.h"
#include "CameraController.h"

#include <memory>

namespace yon {

class Application: public std::enable_shared_from_this<Application> {
public:
  void Run();

  const Window& GetMainWindow() const { return m_window; }

  static std::shared_ptr<Application> Get();

private:
  Application() = default;
  Application(const Application&) = delete;
  Application& operator=(const Application&) = delete;

private:
  void OnEvent(IEvent& event);

private:
  Window m_window;
  CameraController m_cameraControl = CameraController(1280.f / 720.f);

  bool m_running = true;
};

}

#endif
