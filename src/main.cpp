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
      std::make_shared<Shader>("resources/shaders/shader.vert", "resources/shaders/shader.frag");
  std::shared_ptr<Shader> shader2 =
      std::make_shared<Shader>("resources/shaders/shader2.vert", "resources/shaders/shader2.frag");
  std::shared_ptr<Mesh> kittyMesh =
      MeshManager::getInstance().getMesh("resources/kitty/kitty.obj");
  std::shared_ptr<Mesh> blockMesh =
      MeshManager::getInstance().getMesh("resources/block/cube.obj");

  std::shared_ptr<Entity> en = std::make_shared<Entity>(kittyMesh, shader1);
  std::shared_ptr<Entity> en2 = std::make_shared<Entity>(blockMesh, shader2);
  en2->setPosition(glm::vec3(2.0f, 1.0f, -2.0f));

  en2->setRotation(glm::vec3(0.0f, 30.0f, 0.0f));
  Camera camera(glm::vec3(2.0f, 2.0f, 5.0f), glm::vec3(0.0f),
                glm::vec3(0.0f, 1.0f, 0.0f), 60.0f, 640.0f / 480.0f, 0.1f,
                100.0f);

  std::vector<std::shared_ptr<Entity>> targets;
  targets.push_back(en);
  targets.push_back(en2);

  Renderer r;

  while (!window.shouldClose()) {
    r.prepare();

    auto pos = en2->getRotation();
    pos.x ++;
    en2->setRotation(pos);
    
    r.render(targets, camera);
    window.update();
  }

  return 0;
}
