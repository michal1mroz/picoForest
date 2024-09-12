#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "../entity/Entity.h"
#include "../entity/Camera.h"
#include "../shaders/Shader.h"

class Renderer{
public:
  void render(std::vector<Entity>& entities, Camera& camera);
private:
  std::unordered_map<size_t, std::vector<Entity>> batchMapping;
  void prepareBatch(std::vector<Entity>& entities);
};

#endif // RENDERER_H
