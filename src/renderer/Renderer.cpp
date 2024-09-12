#include "Renderer.h"

void Renderer::render(std::vector<Entity> &entities, Camera &camera) { 
  
  for(const auto& entry: entities){
    Shader sh = *(entry.getShader());
    sh.use();
    sh.setUniform("view", camera.getViewMatrix());
    sh.setUniform("projection", camera.getProjectionMatrix());
    entry.draw();
  }
}
