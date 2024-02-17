#include "Kitty.h"

float Kitty::vertices[] = {
    -1.0f, -1.0f, -1.0f,
    -1.0f, 1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, 1.0f, -1.0f,
    -1.0f, -1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, -1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,

    //ears
    0.2f, 1.0f, 0.5f,
    0.7f, 1.0f, 0.8f,
    0.7f, 1.0f, 0.2f,
    0.7f, 1.7f, 0.5f,

    0.2f, 1.0f, -0.5f,
    0.7f, 1.0f, -0.8f,
    0.7f, 1.0f, -0.2f,
    0.7f, 1.7f, -0.5f,
};

unsigned int Kitty::indices[] = {
    0, 1, 2,
    1, 2, 3,
    2, 3, 6,
    3, 6, 7,
    1, 3, 5,
    3, 5, 7,

    //ears
    8, 9, 11,
    8, 10, 11,

    12, 13, 15,
    12, 14, 15,
};

Kitty::Kitty(unsigned int shaderProgram, int posX, int posY)
    : RawObject(shaderProgram, posX, posY, vertices, sizeof(vertices)/sizeof(float),indices, sizeof(indices)/sizeof(unsigned int)) {};

void Kitty::render(){
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(unsigned int),GL_UNSIGNED_INT,0);
}
