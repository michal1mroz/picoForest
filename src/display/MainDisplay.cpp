#include "MainDisplay.h"

// Public
MainDisplay::MainDisplay(int width, int height, const std::string &title)
    : window{nullptr, glfwDestroyWindow}, WIDTH{width}, HEIGHT{height}{
  glfwSetErrorCallback(errorCallback);
  if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW" << std::endl;
    exit(-1);
  }

  GLFWwindow *raw_ptr =
      glfwCreateWindow(this->WIDTH, this->HEIGHT, title.c_str(), NULL, NULL);
  if (!raw_ptr) {
    glfwTerminate();
    std::cerr << "Failde to create GLFW window" << std::endl;
    exit(-1);
  }
  window.reset(raw_ptr);
  glfwMakeContextCurrent(this->window.get());
  glewInit();
}

MainDisplay::~MainDisplay() {
  std::cout << "GLFW window terminating\n";
  this->window.reset(); // to prevent the 65537 error
  glfwTerminate();
}

void MainDisplay::update() {
  glfwSwapBuffers(this->window.get());
  glfwPollEvents();
}

bool MainDisplay::shouldClose() const {
  return glfwWindowShouldClose(this->window.get());
}

// Private
void MainDisplay::errorCallback(int error, const char *description) {
  std::cerr << "GLFW error in MainDisplay\n";
  std::cerr << "GLFW error code: " << error
            << "\nError message: " << description << std::endl;
}
