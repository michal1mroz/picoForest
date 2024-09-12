#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "display/MainDisplay.h"
#include "entity/Camera.h"
#include "entity/Entity.h"
#include "meshes/Mesh.h"
#include "meshes/MeshLoader.h"
#include "shaders/Shader.h"

auto null_mesh = [](Mesh *ptr) {};
auto null_shrdr = [](Shader *ptr) {};

int main() {
  MainDisplay window;
  Shader shader("src/shader.vert", "src/shader.frag");

  MeshLoader md;
  auto x = md.loadFromObj("resources/kitty/kitty.obj");
  Mesh m(x);

  std::shared_ptr<Mesh> mesh_ptr = std::shared_ptr<Mesh>(&m, null_mesh);
  std::shared_ptr<Shader> shader_ptr =
      std::shared_ptr<Shader>(&shader, null_shrdr);

  Entity en(mesh_ptr, shader_ptr);

  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  Camera camera(glm::vec3(2.0f, 2.0f, 5.0f), glm::vec3(0.0f),
                glm::vec3(0.0f, 1.0f, 0.0f), 60.0f, 640.0f / 480.0f, 0.1f,
                100.0f);

  glEnable(GL_DEPTH_TEST);
  while (!window.shouldClose()) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader.use();
    shader.setUniform("view", camera.getViewMatrix());
    shader.setUniform("projection", camera.getProjectionMatrix());

    auto r = en.getRotation();
    r.y++;
    en.setRotation(r);
    en.draw();
    window.update();
  }

  return 0;
}
