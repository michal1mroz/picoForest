#include "Renderer.h"

/*
*   Uses getHash and getShader() methods to first map the id of shader
*   onto vector of entities and then by looping over those idies
*   batch renders every object with a given shader
*/

void Renderer::render(std::vector<Entity> &entities, Camera &camera) { 
  prepareBatch(entities); 
  for(auto& pair: batchMapping){
    std::vector<Entity> batch = pair.second;
    if(!batch.empty()){
      auto& shader = batch[0].getShader();
      shader->use();
      shader->setUniform("view", camera.getViewMatrix());
      shader->setUniform("projection", camera.getProjectionMatrix());
      for(auto& entity: batch){
        entity.draw();
      }
    }
  }
}

void Renderer::prepareBatch(std::vector<Entity>& entities){
  batchMapping.clear();
  for(const auto& entity: entities){
    batchMapping[entity.getHash()].push_back(entity);
  }
}
