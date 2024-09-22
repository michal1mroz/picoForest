#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "../entity/Entity.h"
#include "../entity/Camera.h"
#include "../shaders/Shader.h"
#include "../entity/Light.h"

class Renderer{
public:
  Renderer();
  void render(std::vector<std::shared_ptr<Entity>>& entities, Camera& camera, Light& light);
  void prepare() const;

private:
  std::unordered_map<size_t, std::vector<std::shared_ptr<Entity>>> batchMapping;
  void prepareBatch(std::vector<std::shared_ptr<Entity>>& entities);
};

#endif // RENDERER_H
