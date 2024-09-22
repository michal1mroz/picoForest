#include "Renderer.h"

/*
 *   Uses getHash and getShader() methods to first map the id of shader
 *   onto vector of entities and then by looping over those idies
 *   batch renders every object with a given shader
 */

Renderer::Renderer() {
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
}

void Renderer::prepare() const {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::render(std::vector<std::shared_ptr<Entity>> &entities, Camera &camera, Light& light) {
  prepareBatch(entities);
  for (auto &pair : batchMapping) {
    std::vector<std::shared_ptr<Entity>> batch = pair.second;
    if (!batch.empty()) {
      auto &shader = batch[0]->getShader();
      shader->use();
      shader->setUniform("view", camera.getViewMatrix());
      shader->setUniform("projection", camera.getProjectionMatrix());
      shader->setUniform("lightPos", light.getPosition());
      shader->setUniform("lightColor", light.getColour());
      shader->setUniform("viewPos", camera.getPosition());
      for (auto &entity : batch) {
        entity->draw();
      }
    }
  }
}

void Renderer::prepareBatch(std::vector<std::shared_ptr<Entity>> &entities) {
  batchMapping.clear();
  for (const auto &entity : entities) {
    batchMapping[entity->getHash()].push_back(entity);
  }
}
