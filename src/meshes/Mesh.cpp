#include "Mesh.h"

Mesh::Mesh(const MeshData &data) { setupMesh(data); }

Mesh::Mesh(const std::string &filePath) {
  MeshLoader loader;
  auto rawMesh = loader.loadFromObj(filePath);
  setupMesh(rawMesh);
}

Mesh::~Mesh() {
  for (auto vbo : this->vbos) {
    glDeleteBuffers(1, &vbo);
  }
  glDeleteVertexArrays(1, &this->vao);
  this->vbos.clear();
}

void Mesh::render() const {
  glBindVertexArray(vao);
  enableVertexArrays();
  glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
  unbindVAO();
}

void Mesh::enableVertexArrays() const {
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);
}

void Mesh::setupMesh(const MeshData &data) {
  createVAO();
  bindIndices(data.indices);
  loadDataToAttributeList(0, data.vertices, 3);
  loadDataToAttributeList(1, data.textures, 2);
  loadDataToAttributeList(2, data.normals, 3);
  unbindVAO();
  indexCount = data.vertices.size();
}

void Mesh::createVAO() {
  glGenVertexArrays(1, &this->vao);
  glBindVertexArray(this->vao);
}

void Mesh::loadDataToAttributeList(int attributeNumb, std::vector<float> data,
                                   int coordinateSize) {
  GLuint vboID;
  glGenBuffers(1, &vboID);
  this->vbos.push_back(vboID);
  glBindBuffer(GL_ARRAY_BUFFER, vboID);
  glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), 
               &data[0], GL_STATIC_DRAW);
  glVertexAttribPointer(attributeNumb, coordinateSize, 
                        GL_FLOAT, GL_FALSE, 0, 0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::bindIndices(std::vector<unsigned int> indices) {
  GLuint vboID;
  glGenBuffers(1, &vboID);
  this->vbos.push_back(vboID);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
               &indices[0], GL_STATIC_DRAW);
}

void Mesh::unbindVAO() const { glBindVertexArray(0); }
