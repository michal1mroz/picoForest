#include "InputManager.h"

void InputManager::pollEvents(GLFWwindow *window) {
  // logging key state
  keyState[MAIN_MOVE_UP] = glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS;
  keyState[MAIN_MOVE_DOWN] = glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS;
  keyState[MAIN_MOVE_LEFT] = glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS;
  keyState[MAIN_MOVE_RIGHT] = glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS;
  keyState[EXIT] = glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS;
  keyState[MOUSE_LEFT_BUTTON] =
      glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;

  // logging mouse position
  static double xPos, yPos;
  glfwGetCursorPos(window, &xPos, &yPos);
  mousePosition = glm::vec2(xPos, yPos);
}

bool InputManager::isCommandActive(Command cmd) { return keyState[cmd]; }
