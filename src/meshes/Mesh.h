#ifndef MESH_H
#define MESH_H

#include "MeshData.h"
#include "MeshLoader.h"
#include <GL/glew.h>

class Mesh {
public:
  Mesh(const MeshData &meshData);
  Mesh(const std::string &filePath);

  ~Mesh();
  void render() const;

private:
  void setupMesh(const MeshData &data);
  void createVAO();
  void loadDataToAttributeList(int attributeNumb, 
      std::vector<float> data, int coordinateSize);
  void bindIndices(std::vector<unsigned int> indices);
  void unbindVAO() const ; 
  void enableVertexArrays() const;

  GLuint vao = 0;
  std::vector<GLuint> vbos;
  size_t indexCount = 0;
};

#endif // MESH_H
