#ifndef MESHDATA_H
#define MESHDATA_H

/*
*  Definition of a struct that stores the data
*  of a given mesh.
*/

#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_float3.hpp>
#include <ostream>
#include <vector>

struct TemporaryMeshData{
  std::vector<glm::vec3> vertices;
  std::vector<glm::vec3> normals;
  std::vector<glm::vec2> textures;
  std::vector<glm::vec3> indices;
};

struct MeshData{
  std::vector<float> vertices;
  std::vector<float> normals;
  std::vector<float> textures;
  std::vector<unsigned int> indices;

  bool isValid() const;
};

#endif // MESHDATA_H
