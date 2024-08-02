#ifndef EVENT_H
#define EVENT_H

namespace yon {

class Event {
public:
enum class Type {
  MouseMoved, MouseButtonPressed, MouseButtonReleased,
  KeyPressed, KeyReleased, KeyHeld,
  WindowResized, WindowClosed
};

struct MouseMoved {
  double pos_x;
  double pos_y;
};

struct MouseButtonPressed {
  int key;
};

struct MouseButtonReleased {
  int key;
};

struct KeyPressed {
  int key;
};

struct KeyReleased {
  int key;
};

struct KeyHeld {
  int key;
};

public:
Event(Type type, void* data) : m_type(type), m_data(data) {}
Type GetType() const { return m_type; }
void* GetData() const { return m_data; }

private:
  Type m_type;
  void* m_data;
};

}

#endif