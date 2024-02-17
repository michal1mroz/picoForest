#include "RawObject.h"

RawObject::RawObject(unsigned int shaderProgram, int posX, int posY, float* vertices, GLsizei vertexCount, unsigned int* indices, GLsizei indexCount)
    : posX(posX), posY(posY), shaderProgram(shaderProgram), indices(indices), vertices(vertices), vertexCount(vertexCount), indexCount(indexCount){
    setup_vertices(posX, posY);
    setup_buffers();
}

RawObject::~RawObject(){
    glDeleteBuffers(1, &this->VBO);
    glDeleteBuffers(1, &this->EBO);
    glDeleteVertexArrays(1, &this->VAO);
}

void RawObject::setup_buffers(){
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);
    glGenBuffers(1, &this->EBO);

    glBindVertexArray(this->VAO);

    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(float), this->vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount*sizeof(unsigned int), this->indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void RawObject::setup_vertices(int posX, int posY){
    int vertCount = sizeof(this->vertices) / sizeof(float);
    for(int i = 0; i < vertCount; i+=3){
        this->vertices[i] = this->vertices[i] + posX;
        this->vertices[i+1] = this->vertices[i+1] + posY;
        this->vertices[i+2] = this->vertices[i+2];
    }
}
