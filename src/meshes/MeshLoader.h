#ifndef MESHLOADER_H
#define MESHLOADER_H

/*
 *   Class for loading mesh data from .obj files
 */

#include "MeshData.h"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

class MeshLoader {
public:
  MeshData loadFromObj(const std::string &path);

private:
  void handleVertex(TemporaryMeshData &data, std::istringstream &stream);
  void handleNormal(TemporaryMeshData &data, std::istringstream &stream);
  void handleTexture(TemporaryMeshData &data, std::istringstream &stream);
  void handleFace(TemporaryMeshData &data, std::istringstream &stream);
  TemporaryMeshData loadToTemporary(const std::string &filePath);
};

#endif // MESHLOADER_H
