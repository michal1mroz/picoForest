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
#include "meshes/MeshManager.h"
#include "renderer/Renderer.h"
#include "shaders/Shader.h"

int main() {
  MainDisplay window;

  std::shared_ptr<Shader> shader1 =
      std::make_shared<Shader>("src/shader.vert", "src/shader.frag");
  std::shared_ptr<Shader> shader2 =
      std::make_shared<Shader>("src/shader2.vert", "src/shader2.frag");
  std::shared_ptr<Mesh> kittyMesh =
      MeshManager::getInstance().getMesh("resources/kitty/kitty.obj");

  Entity en("resources/kitty/kitty.obj", shader1);
  Entity en2(kittyMesh, shader2);
  en2.setPosition(glm::vec3(3.0f, 1.0f, -5.0f));

  Camera camera(glm::vec3(2.0f, 2.0f, 5.0f), glm::vec3(0.0f),
                glm::vec3(0.0f, 1.0f, 0.0f), 60.0f, 640.0f / 480.0f, 0.1f,
                100.0f);

  std::vector<Entity> targets;
  targets.push_back(en);
  targets.push_back(en2);

  Renderer r;

  while (!window.shouldClose()) {
    r.prepare();
    r.render(targets, camera);
    window.update();
  }

  return 0;
}
