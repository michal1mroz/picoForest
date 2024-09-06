#ifndef MESHLOADER_H
#define MESHLOADER_H

/*
*   Class for loading mesh data from .obj files
*/

#include "MeshData.h"
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <iostream>

class MeshLoader{
public:
  MeshData loadFromObj(const std::string& path);

private:
  void handleVertex(MeshData& data, std::istringstream& stream);
  void handleNormal(MeshData& data, std::istringstream& stream);
  void handleTexture(MeshData& data, std::istringstream& stream);
  void handleFace(MeshData& data, std::istringstream& stream);
};

#endif // MESHLOADER_H
