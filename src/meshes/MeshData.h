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

struct MeshData{
  std::vector<glm::vec3> vertices;
  std::vector<glm::vec3> normals;
  std::vector<glm::vec2> texCoords;
  std::vector<unsigned int> vertexInd;
  std::vector<unsigned int> normalInd;
  std::vector<unsigned int> texInd;

  bool isValid() const;
};

#endif // MESHDATA_H
