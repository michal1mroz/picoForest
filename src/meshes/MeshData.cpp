#include "MeshData.h"

bool MeshData::isValid() const {
  return !vertices.empty() &&
         (!normals.empty() || normals.size() == vertices.size()) &&
         (!textures.empty() || textures.size() == vertices.size());
}

