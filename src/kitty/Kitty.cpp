#include "Kitty.h"

float vertices[] = {
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

unsigned int indices[] = {
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

Kitty::Kitty(unsigned int shaderProgram, int posX, int posY) : shaderProgram(shaderProgram){
        this->load_vertices_kitty(posX, posY);
        this->buffer_setup();
}

void Kitty::render(){
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, sizeof(index)/sizeof(unsigned int), GL_UNSIGNED_INT, 0);
}

void Kitty::load_vertices_kitty(int x, int y){
        int vertCount = sizeof(vertices)/sizeof(vertices[0]);
        for(int i = 0; i < vertCount; i+=3){
            this->vert[i] = vertices[i] + x;
            this->vert[i+1] = vertices[i+1] + y;
            this->vert[i+2] = vertices[i+2];
        }
        std::copy(std::begin(indices), std::end(indices), std::begin(index));
}

void Kitty::buffer_setup(){
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(this->vert), this->vert, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), nullptr);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
}