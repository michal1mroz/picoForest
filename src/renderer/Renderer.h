#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "../entity/Entity.h"
#include "../entity/Camera.h"
#include "../shaders/Shader.h"

class Renderer{
public:
  void render(std::vector<Entity>& entities, Camera& camera);
};

#endif // RENDERER_H
