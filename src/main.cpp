#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "display/InputManager.h"
#include "display/MainDisplay.h"
#include "entity/Camera.h"
#include "entity/Entity.h"
#include "entity/Light.h"
#include "entity/MovableEntities/Kitty.h"
#include "entity/StaticEntity.h"
#include "meshes/Mesh.h"
#include "meshes/MeshManager.h"
#include "physicsEngine/PhysicsEngine.h"
#include "renderer/Renderer.h"
#include "shaders/Shader.h"

int main() {
  MainDisplay window(1920, 1080);

  std::shared_ptr<Shader> shader1 = std::make_shared<Shader>(
      "resources/shaders/shader.vert", "resources/shaders/shader.frag");
  std::shared_ptr<Shader> shader2 = std::make_shared<Shader>(
      "resources/shaders/shader2.vert", "resources/shaders/shader2.frag");
  std::shared_ptr<Mesh> blockMesh =
      MeshManager::getInstance().getMesh("resources/block/cube.obj");

  std::shared_ptr<MovableEntity> en = std::make_shared<Kitty>(shader1);
  auto position = glm::vec3(0.0f, 0.0f, 20.0f);
  auto target = glm::vec3(0.0f);
  auto up = glm::vec3(0.0f, 1.0f, 0.0f);
  auto aspectRatio = window.getAspectRatio();

  Camera camera(position, target, up, 60.0f, aspectRatio, 0.1f, 100.0f);

  Light light(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.9f, 1.0f, 0.9f));

  std::vector<std::shared_ptr<Entity>> targets;
  targets.push_back(en);

  for (int i = -5; i < 5; i++) {
    std::shared_ptr<StaticEntity> tmp1 =
        std::make_shared<StaticEntity>(blockMesh, shader2);
    tmp1->setPosition(glm::vec3(i * 2.0f, i * 2.0f, 0.0f));
    targets.push_back(tmp1);
    std::shared_ptr<StaticEntity> tmp2 =
        std::make_shared<StaticEntity>(blockMesh, shader2);
    tmp2->setPosition(glm::vec3(i * 2.0f, -10.0f, 0.0f));
    targets.push_back(tmp2);
  }
  Renderer r;

  InputManager &input = InputManager::getInstance();

  double lastTime = glfwGetTime();
  double deltaTime = 0.0;
  std::vector<std::shared_ptr<MovableEntity>> x;
  x.push_back(en);

  en->setPosition(glm::vec3(-4.0f, 4.0f, 0.0f));
  while (!window.shouldClose()) {
    double currentTime = glfwGetTime();
    deltaTime = currentTime - lastTime;
    lastTime = currentTime;

    input.pollEvents(window.getWindowPtr());
    r.prepare();
    PhysicsEngine::Update(deltaTime, x, targets);
    camera.handleMouseDrag();
    r.render(targets, camera, light);
    window.update();

    if (input.isCommandActive(InputManager::EXIT)) {
      break;
    }
  }

  return 0;
}
