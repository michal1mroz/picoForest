#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "display/MainDisplay.h" 
#include "meshes/Mesh.h"
#include "meshes/MeshLoader.h"
#include "shaders/Shader.h"

int main() {
  MainDisplay window;
  Shader shader("src/shader.vert", "src/shader.frag");

  MeshLoader md;
  auto x = md.loadFromObj("resources/kitty/kitty.obj");
  Mesh m(x);

  auto proj =
      glm::perspective(glm::radians(60.0f), 640.f / 480.f, 0.1f, 100.0f);
  
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  
  glEnable(GL_DEPTH_TEST);
  while (!window.shouldClose()) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader.use();
    shader.setUniform("projection", proj);

    m.render();
    window.update();
  }
  return 0;
}
