#include "Shader.h"

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath){
  std::string vertexSource = this->loadShaderSource(vertexPath);
  std::string fragmentSource = this->loadShaderSource(fragmentPath);

  auto vertexShader = compileShader(vertexSource, GL_VERTEX_SHADER);
  auto fragmentShader = compileShader(fragmentSource, GL_FRAGMENT_SHADER);

  if(vertexShader && fragmentShader) linkProgram(vertexShader, fragmentShader);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

Shader::~Shader(){
  if(programID != 0) glDeleteProgram(programID);
}

void Shader::checkCompileErrors(GLuint shader, GLenum type){
  GLint success;
  GLchar infoLog[1024];
  if(type != GL_PROGRAM){
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success){
      glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
      std::cerr << "Error: Shader compilation error\n";
      std::cerr << "Type: " << (type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT");
      std::cerr << "\n" << infoLog << std::endl;
    }
  }else{
    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if(!success){
      glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
      std::cerr << "Error: program linking error:\n";
      std::cerr << infoLog << std::endl;
    }
  }
}

std::string Shader::loadShaderSource(const std::string& path){
  std::ifstream file(path);
  if(!file.is_open()){
    std::cerr << "Failed to open shader file: " << path;
    std::cerr << "\nProgram finishing\n";
    exit(EXIT_FAILURE);
  }
  std::stringstream buffer;
  buffer << file.rdbuf();
  file.close();
  return buffer.str();
}

GLuint Shader::compileShader(const std::string& source, GLenum type){
  GLuint shader = glCreateShader(type);
  const char* src = source.c_str();
  glShaderSource(shader, 1, &src, nullptr);
  glCompileShader(shader);

  checkCompileErrors(shader, type);

  return shader;
}

void Shader::linkProgram(GLuint vertexShader, GLuint fragmentShader){
  this->programID = glCreateProgram();
  glAttachShader(programID, vertexShader);
  glAttachShader(programID, fragmentShader);
  glLinkProgram(programID);

  checkCompileErrors(programID, GL_PROGRAM);
}

void Shader::use() const{
  if(programID != 0) glUseProgram(programID);
}

void Shader::setUniform(const std::string& name, int value){
  glUniform1i(getUniformLocation(name), value);
}

void Shader::setUniform(const std::string& name, float value){
  glUniform1f(getUniformLocation(name), value);
}

void Shader::setUniform(const std::string& name, const glm::vec3& value){
  glUniform3fv(getUniformLocation(name), 1, &value[0]);
}

void Shader::setUniform(const std::string& name, const glm::mat4& value){
  glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &value[0][0]);
}

GLint Shader::getUniformLocation(const std::string& name){
  if(uniformCache.find(name) != uniformCache.end()){
    return uniformCache[name];
  }
  auto location = glGetUniformLocation(programID, name.c_str());
  if(location == -1){
    std::cerr << "Warning: Uniform " << name << " doesn't exist!" << std::endl;
  }

  uniformCache[name] = location;
  return location;
}

GLuint Shader::getProgramID(){
  return this->programID;
}
