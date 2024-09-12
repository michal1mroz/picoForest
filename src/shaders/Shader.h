#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_map>

class Shader{
private:
  std::string loadShaderSource(const std::string& filePath);
  GLuint compileShader(const std::string& source, GLenum shaderType);
  void linkProgram(GLuint vertexShader, GLuint fragmentShader);
  void checkCompileErrors(GLuint shader, GLenum type);
  GLint getUniformLocation(const std::string& name);

  GLuint programID;
  std::unordered_map<std::string, GLint> uniformCache;
public:
  Shader(const std::string& vertexPath, const std::string& fragmentPath);
  ~Shader();

  bool operator ==(const Shader& other) const;
  GLuint getProgramID() const;
  
  void use() const;
  void setUniform(const std::string& name, int value);
  void setUniform(const std::string& name, float value);
  void setUniform(const std::string& name, const glm::vec3& value);
  void setUniform(const std::string& name, const glm::mat4& value);
};

namespace std{
  template<>
  struct hash<Shader> {
    std::size_t operator()(const Shader& shader) const{
      return std::hash<GLuint>{}(shader.getProgramID());
  }
  };
}
#endif // SHADER_H
