#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "MainDisplay.h"
#include <glm/ext/vector_float2.hpp>
#include <unordered_map>

/*
 * Another singleton pattern to handle input
 */

class InputManager {
public:
  static InputManager &getInstance() {
    static InputManager instance;
    return instance;
  }

  enum Command {
    MAIN_MOVE_UP,
    MAIN_MOVE_DOWN,
    MAIN_MOVE_LEFT,
    MAIN_MOVE_RIGHT,
    MOUSE_LEFT_BUTTON,
    EXIT,
  };

  void pollEvents(GLFWwindow *window);
  bool isCommandActive(Command cmd);
  glm::vec2 getMousePosition(){return mousePosition;};
private:
  std::unordered_map<Command, bool> keyState;
  double mouseX, mouseY;
  glm::vec2 mousePosition;
};

#endif // INPUTMANAGER_H
