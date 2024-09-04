#ifndef MAINDISPLAY_H
#define MAINDISPLAY_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <string>
#include <iostream>

class MainDisplay{
private:
  static void errorCallback(int error, const char* description);

  std::unique_ptr<GLFWwindow, void(*)(GLFWwindow*)> window;
  // idc about resizing so it's not static const.
  int WIDTH;
  int HEIGHT;
   

public: 
  MainDisplay(int width = 640, int height = 480, const std::string& title = "OpenGL Test");
  virtual ~MainDisplay();

  // No resizing for you lil boy
  MainDisplay(const MainDisplay&) = delete;
  MainDisplay& operator=(const MainDisplay&) = delete;
  MainDisplay(MainDisplay&&) = delete;
  MainDisplay& operator=(MainDisplay&&) = delete;

  void update();
  bool shouldClose() const;
};

#endif // MAINDISPLAY_H
