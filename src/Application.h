
#include "Window.h"

namespace yon {

class Application {
public:
  void Run();

private:
  void OnEvent(IEvent& event);
private:
  Window m_window;
  bool m_running = true;
};

}