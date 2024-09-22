#include "MeshManager.h"

std::shared_ptr<Mesh> MeshManager::getMesh(const std::string& filePath){
  auto val = meshes.find(filePath);
  if(val != meshes.end()){
    return val->second;
  }
  std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>(filePath);
  meshes[filePath] = mesh;
  return mesh;
}

