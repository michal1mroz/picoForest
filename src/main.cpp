#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "display/MainDisplay.h"
#include "display/InputManager.h"
#include "entity/Camera.h"
#include "entity/Entity.h"
#include "entity/Kitty.h"
#include "entity/Light.h"
#include "meshes/Mesh.h"
#include "meshes/MeshManager.h"
#include "renderer/Renderer.h"
#include "shaders/Shader.h"

int main() {
  MainDisplay window;

  std::shared_ptr<Shader> shader1 =
      std::make_shared<Shader>("resources/shaders/shader.vert", "resources/shaders/shader.frag");
  std::shared_ptr<Shader> shader2 =
      std::make_shared<Shader>("resources/shaders/shader2.vert", "resources/shaders/shader2.frag");
  std::shared_ptr<Mesh> blockMesh =
      MeshManager::getInstance().getMesh("resources/block/cube.obj");

  std::shared_ptr<Entity> en = std::make_shared<Kitty>(shader1);
  std::shared_ptr<Entity> en2 = std::make_shared<Kitty>(shader2);
  en2->setPosition(glm::vec3(2.0f, 1.0f, -2.0f));

  en2->setRotation(glm::vec3(0.0f, 30.0f, 0.0f));
  Camera camera(glm::vec3(2.0f, 2.0f, 5.0f), glm::vec3(0.0f),
                glm::vec3(0.0f, 1.0f, 0.0f), 60.0f, 640.0f / 480.0f, 0.1f,
                100.0f);

  Light light(glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.5f));
  std::vector<std::shared_ptr<Entity>> targets;
  targets.push_back(en);
  targets.push_back(en2);

  Renderer r;

  InputManager& input = InputManager::getInstance();

  while (!window.shouldClose()) {
    input.pollEvents(window.getWindowPtr()); 
    r.prepare();

    en->move();

    r.render(targets, camera, light);
    window.update();

    if(input.isCommandActive(InputManager::EXIT)){
      break;
    } 
  }

  return 0;
}
