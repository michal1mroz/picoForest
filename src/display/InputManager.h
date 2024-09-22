#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "MainDisplay.h"
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
    EXIT,
  };

  void pollEvents(GLFWwindow* window);
  bool isCommandActive(Command cmd);
private:
  std::unordered_map<Command, bool> keyState;
};

#endif // INPUTMANAGER_H
