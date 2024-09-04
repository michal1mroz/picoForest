#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <vector>

#include "display/MainDisplay.h"

float vertices[] = {
    -1.0f,
    -1.0f,
    -1.0f,
    -1.0f,
    1.0f,
    -1.0f,
    1.0f,
    -1.0f,
    -1.0f,
    1.0f,
    1.0f,
    -1.0f,
    -1.0f,
    -1.0f,
    1.0f,
    -1.0f,
    1.0f,
    1.0f,
    1.0f,
    -1.0f,
    1.0f,
    1.0f,
    1.0f,
    1.0f,

    // ears
    -0.2f,
    1.0f,
    0.5f,
    0.7f,
    1.0f,
    0.8f,
    0.7f,
    1.0f,
    0.2f,
    0.7f,
    1.9f,
    0.5f,

    -0.2f,
    1.0f,
    -0.5f,
    0.7f,
    1.0f,
    -0.8f,
    0.7f,
    1.0f,
    -0.2f,
    0.7f,
    1.9f,
    -0.5f,

};

unsigned int indices[] = {
    0,
    1,
    2,
    1,
    2,
    3,
    2,
    3,
    6,
    3,
    6,
    7,
    1,
    3,
    5,
    3,
    5,
    7,

    // ears
    8,
    9,
    11,
    8,
    10,
    11,

    12,
    13,
    15,
    12,
    14,
    15,

};

typedef std::vector<float> vertex;

vertex normalize(vertex a) {
  float length = std::sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
  return {
      a[0] / length,
      a[1] / length,
      a[2] / length,
  };
}

vertex normal(vertex v1, vertex v2, vertex v3) {
  vertex a{
      v1[0] - v2[0],
      v1[1] - v2[1],
      v1[2] - v2[2],
  };

  vertex b{
      v1[0] - v3[0],
      v1[1] - v3[1],
      v1[2] - v3[2],
  };

  return normalize({
      a[1] * b[2] - a[2] * b[1],
      a[2] * b[0] - a[0] * b[2],
      a[0] * b[1] - a[1] * b[0],
  });
};

std::vector<float> generate_vertex_data() {
  std::vector<float> result;
  int triangle_count = sizeof(indices) / sizeof(unsigned int) / 3;

  for (int t = 0; t < triangle_count; t++) {
    vertex v1{
        vertices[indices[t * 3] * 3],
        vertices[indices[t * 3] * 3 + 1],
        vertices[indices[t * 3] * 3 + 2],
    };
    vertex v2{
        vertices[indices[t * 3 + 1] * 3],
        vertices[indices[t * 3 + 1] * 3 + 1],
        vertices[indices[t * 3 + 1] * 3 + 2],
    };
    vertex v3{
        vertices[indices[t * 3 + 2] * 3],
        vertices[indices[t * 3 + 2] * 3 + 1],
        vertices[indices[t * 3 + 2] * 3 + 2],
    };

    vertex n = normal(v1, v2, v3);

    result.insert(result.end(), v1.begin(), v1.end());
    result.insert(result.end(), n.begin(), n.end());
    result.insert(result.end(), v2.begin(), v2.end());
    result.insert(result.end(), n.begin(), n.end());
    result.insert(result.end(), v3.begin(), v3.end());
    result.insert(result.end(), n.begin(), n.end());
  }
  return result;
}

int load_shader(std::string filename, int kind) {
  std::ifstream ifs(filename);
  std::string shader_source((std::istreambuf_iterator<char>(ifs)),
                            std::istreambuf_iterator<char>());

  auto str = shader_source.c_str();

  unsigned int shader = glCreateShader(kind);
  glShaderSource(shader, 1, &str, nullptr);
  glCompileShader(shader);

  int status;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

  if (!status) {
    char info[512];
    glGetShaderInfoLog(shader, 512, nullptr, info);
    std::cerr << info << std::endl;
    exit(-1);
  }

  return shader;
}

int main() {
  MainDisplay window;

  auto vertex_shader = load_shader("src/shader.vert", GL_VERTEX_SHADER);
  auto fragment_shader = load_shader("src/shader.frag", GL_FRAGMENT_SHADER);
  auto shader_program = glCreateProgram();
  glAttachShader(shader_program, vertex_shader);
  glAttachShader(shader_program, fragment_shader);
  glLinkProgram(shader_program);

  int status;
  glGetProgramiv(shader_program, GL_LINK_STATUS, &status);
  if (!status) {
    char info[512];
    glGetProgramInfoLog(shader_program, 512, nullptr, info);
    std::cerr << info << std::endl;
    exit(-1);
  }

  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);

  auto vertex_data = generate_vertex_data();

  unsigned int vbo;
  glGenBuffers(1, &vbo);

  unsigned int vao;
  glGenVertexArrays(1, &vao);

  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, vertex_data.size() * sizeof(float),
               &vertex_data[0], GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), nullptr);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  int proj_loc = glGetUniformLocation(shader_program, "projection");
  auto proj =
      glm::perspective(glm::radians(60.0f), 640.f / 480.f, 0.1f, 100.0f);

  glEnable(GL_DEPTH_TEST);
  while (!window.shouldClose()) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(shader_program);
    glUniformMatrix4fv(proj_loc, 1, GL_FALSE, glm::value_ptr(proj));
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, vertex_data.size());

    window.update();
  }
  return 0;
}
