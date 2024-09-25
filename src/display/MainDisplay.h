#ifndef MAINDISPLAY_H
#define MAINDISPLAY_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <memory>
#include <string>

class MainDisplay {
private:
  static void errorCallback(int error, const char *description);

  std::unique_ptr<GLFWwindow, void (*)(GLFWwindow *)> window;
  int WIDTH;
  int HEIGHT;

public:
  MainDisplay(int width = 640, int height = 480,
              const std::string &title = "OpenGL Test");
  virtual ~MainDisplay();

  // No resizing for you lil boy
  MainDisplay(const MainDisplay &) = delete;
  MainDisplay &operator=(const MainDisplay &) = delete;
  MainDisplay(MainDisplay &&) = delete;
  MainDisplay &operator=(MainDisplay &&) = delete;

  GLFWwindow* getWindowPtr(){return this->window.get();}
  float getAspectRatio(){return (float)WIDTH / HEIGHT; }

  void update();
  bool shouldClose() const;
};

#endif // MAINDISPLAY_H
