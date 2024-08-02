#include "Core.h"

#include "Window.h"

namespace yon {

Window::~Window() {
  glfwDestroyWindow(m_window);
  glfwTerminate();
}

void Window::Create(int width, int height, std::string title) {
  auto success = glfwInit();
  ASSERT(success);

  m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
  m_context.Create(m_window);

  glfwSetWindowUserPointer(m_window, &m_data);

  glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xpos, double ypos)
                                        {
                                          auto window_data =
                                            reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(window));

                                          Event::MouseMoved data;
                                          data.pos_x = xpos;
                                          data.pos_y = ypos;

                                          Event event(Event::Type::MouseMoved, &data);
                                          window_data->m_callback(event);
                                        });

  glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
                                  {
                                    auto window_data =
                                      reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(window));

                                    switch(action) {
                                      case GLFW_PRESS:
                                      {
                                        Event::KeyPressed data;
                                        data.key = key;
                                        Event event(Event::Type::KeyPressed, &data);
                                        window_data->m_callback(event);
                                        break;
                                      }

                                      case GLFW_RELEASE:
                                      {
                                        Event::KeyReleased data;
                                        data.key = key;
                                        Event event(Event::Type::KeyReleased, &data);
                                        window_data->m_callback(event);
                                        break;
                                      }

                                      case GLFW_REPEAT:
                                      {
                                        Event::KeyHeld data;
                                        data.key = key;
                                        Event event(Event::Type::KeyHeld, &data);
                                        window_data->m_callback(event);
                                        break;
                                      }

                                      default:
                                        break;
                                    }
                                  });

  glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window)
                                          {
                                            auto window_data =
                                              reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(window));
                                            Event event(Event::Type::WindowClosed, nullptr);
                                            window_data->m_callback(event);
                                          });
}

void Window::Update() {
  m_context.SwapBuffers();
  glfwPollEvents();
}

}
