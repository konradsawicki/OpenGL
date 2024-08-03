#ifndef EVENT_H
#define EVENT_H

namespace yon {

enum class EventType {
  MouseMove, MouseButtonPress, MouseButtonRelease,
  KeyPress, KeyRelease, KeyHold,
  WindowResize, WindowClose
};

class IEvent {
public:
  virtual EventType GetType() const = 0;

public:
  bool handled = false;
};

class MouseMoveEvent : public IEvent {
public:
  MouseMoveEvent(double posx, double posy) : m_posx(posx), m_posy(posy) {}

  static EventType GetStaticType() { return EventType::MouseMove; }
  virtual EventType GetType() const { return GetStaticType(); }

public:
  double m_posx;
  double m_posy;
};

class IKeyEvent : public IEvent {
public:
  IKeyEvent(int key) : m_key(key) {}

public:
  int m_key;
};

class KeyPressEvent : public IKeyEvent {
public:
  KeyPressEvent(int key) : IKeyEvent(key) {}

  static EventType GetStaticType() { return EventType::KeyPress; }
  virtual EventType GetType() const { return GetStaticType(); }
};

class KeyReleaseEvent : public IKeyEvent {
public:
  KeyReleaseEvent(int key) : IKeyEvent(key) {}

  static EventType GetStaticType() { return EventType::KeyRelease; }
  virtual EventType GetType() const { return GetStaticType(); }
};

class KeyHoldEvent : public IKeyEvent {
public:
  KeyHoldEvent(int key) : IKeyEvent(key) {}

  static EventType GetStaticType() { return EventType::KeyHold; }
  virtual EventType GetType() const { return GetStaticType(); }
};


class WindowCloseEvent : public IEvent {
public:
  static EventType GetStaticType() { return EventType::WindowClose; }
  virtual EventType GetType() const { return GetStaticType(); }
};

}

#endif