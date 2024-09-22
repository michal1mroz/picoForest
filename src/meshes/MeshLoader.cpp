#include "MeshLoader.h"
#include "MeshData.h"

MeshData MeshLoader::loadFromObj(const std::string &filePath) {
  TemporaryMeshData tmpData = loadToTemporary(filePath);
  MeshData result;

  for (auto index : tmpData.indices) {
    if (index.y >= 0) {
      glm::vec2 texture = tmpData.textures.at(index.y);
      result.textures.push_back(texture.x);
      result.textures.push_back(texture.y);
    }
    if (index.z >= 0) {
      glm::vec3 normal = tmpData.normals.at(index.z);
      result.normals.push_back(normal.x);
      result.normals.push_back(normal.y);
      result.normals.push_back(normal.z);
    }
  }
  for (auto vertex : tmpData.vertices) {
    result.vertices.push_back(vertex.x);
    result.vertices.push_back(vertex.y);
    result.vertices.push_back(vertex.z);
  }
  for (long unsigned int i = 0; i < tmpData.indices.size(); i++) {
    result.indices.push_back(tmpData.indices.at(i).x);
  }
  return result;
}

TemporaryMeshData MeshLoader::loadToTemporary(const std::string &filePath) {
  TemporaryMeshData tmpData;
  std::ifstream file(filePath);
  if (!file.is_open()) {
    std::cerr << "Error: MeshLoader failed to open: " << filePath << std::endl;
    exit(EXIT_FAILURE);
  }

  std::string line;
  while (std::getline(file, line)) {
    std::istringstream iss(line);
    std::string type;
    iss >> type;
    if (type == "v") {
      handleVertex(tmpData, iss);
    } else if (type == "vt") {
      handleTexture(tmpData, iss);
    } else if (type == "vn") {
      handleNormal(tmpData, iss);
    } else if (type == "f") {
      handleFace(tmpData, iss);
    }
  }
  file.close();
  return tmpData;
}

void MeshLoader::handleVertex(TemporaryMeshData &data,
                              std::istringstream &stream) {
  glm::vec3 vertex;
  stream >> vertex.x >> vertex.y >> vertex.z;
  data.vertices.push_back(vertex);
}

void MeshLoader::handleTexture(TemporaryMeshData &data,
                               std::istringstream &stream) {
  glm::vec2 texture;
  stream >> texture.x >> texture.y;
  data.textures.push_back(texture);
}

void MeshLoader::handleNormal(TemporaryMeshData &data,
                              std::istringstream &stream) {
  glm::vec3 normal;
  stream >> normal.x >> normal.y >> normal.z;
  data.normals.push_back(normal);
}

void MeshLoader::handleFace(TemporaryMeshData &data,
                            std::istringstream &stream) {
  std::string vertexData;
  while (stream >> vertexData) {
    std::istringstream vertexStream(vertexData);
    std::string index;
    glm::vec3 line;
    line.x = -1, line.y = -1, line.z = -1;

    if (std::getline(vertexStream, index, '/')) {
      line.x = std::stoi(index) - 1;
    }

    if (std::getline(vertexStream, index, '/')) {
      if (!index.empty()) {
        line.y = std::stoi(index) - 1;
      }
    }

    if (std::getline(vertexStream, index, '/')) {
      if (!index.empty()) {
        line.z = std::stoi(index) - 1;
      }
    }
    data.indices.push_back(line);
  }
}
