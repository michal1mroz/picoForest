#ifndef MESHMANAGER_H
#define MESHMANAGER_H

/*
*  Singleton pattern, just so we can say we've used it.
*  This class caches all meshes loaded based on the file paths,
*  to avoid loading each object into the memory more than once
*/

#include "Mesh.h"
#include <memory>
#include <unordered_map>

class MeshManager{
public:
  static MeshManager& getInstance(){
    static MeshManager instance;
    return instance;
  }
  std::shared_ptr<Mesh> getMesh(const std::string& filePath);

  MeshManager(const MeshManager&) = delete;
  MeshManager& operator=(const MeshManager&) = delete;
private:
  MeshManager() = default;

  std::unordered_map<std::string, std::shared_ptr<Mesh>> meshes;
};

#endif // MESHMANAGER_H
