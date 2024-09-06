#include "MeshLoader.h"

MeshData MeshLoader::loadFromObj(const std::string& filePath) {
  MeshData data;

  std::ifstream file(filePath);
  if(!file.is_open()){
    std::cerr << "Error: MeshLoader failed to open: " << filePath << std::endl;
    exit(EXIT_FAILURE);
  }

  std::string line;
  while(std::getline(file, line)){
    std::istringstream iss(line);
    std::string type;
    iss >> type;
    if(type == "v"){
      handleVertex(data, iss);   
    }
    else if (type == "vt"){
      handleTexture(data, iss);
    }
    else if(type == "vn"){
      handleNormal(data, iss);
    }
    else if(type == "f"){
      handleFace(data, iss);
    }
  }
  file.close();

  return data;
}

void MeshLoader::handleVertex(MeshData& data, std::istringstream& stream){
  glm::vec3 vertex;
  stream >> vertex.x >> vertex.y >> vertex.z;
  data.vertices.push_back(vertex);
}

void MeshLoader::handleTexture(MeshData& data, std::istringstream& stream){
  glm::vec2 texture;
  stream >> texture.x >> texture.y;
  data.texCoords.push_back(texture);
}

void MeshLoader::handleNormal(MeshData& data, std::istringstream& stream){
  glm::vec3 normal;
  stream >> normal.x >> normal.y >> normal.z;
  data.normals.push_back(normal);
}

void MeshLoader::handleFace(MeshData& data, std::istringstream& stream){
  std::string vertexData;
  while(stream >> vertexData){
    std::istringstream vertexStream(vertexData);
    std::string index;

    unsigned int vertexIndex = 0, textureIndex = 0, normalIndex = 0;
    if(std::getline(vertexStream, index, '/')){
      vertexIndex = std::stoi(index);
      data.vertexInd.push_back(vertexIndex - 1);
    }

    if(std::getline(vertexStream, index, '/')){
      if(!index.empty()){
        textureIndex = std::stoi(index);
        data.texInd.push_back(textureIndex - 1);
      }
    }

    if(std::getline(vertexStream, index, '/')){
      if(!index.empty()){
        normalIndex = std::stoi(index);
        data.normalInd.push_back(normalIndex - 1);
      }
    }
  }
}

