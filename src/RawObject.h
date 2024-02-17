#ifndef RAWOBJECT_H
#define RAWOBJECT_H

#include <GL/glew.h>
#include <iostream>

class RawObject{
protected:
    int posX, posY;
    
    float* vertices;
    unsigned int* indices;
    unsigned int VBO, EBO, VAO;
    unsigned int shaderProgram;

    GLsizei vertexCount;
    GLsizei indexCount;

    void setup_buffers();
    void setup_vertices(int posX, int posY);

public:

    RawObject(unsigned int shaderProgram, int posX, int posY, float* vertices, GLsizei vertexCount, unsigned int* indices, GLsizei indexCount);
    virtual ~RawObject();
    virtual void render() = 0;
};

#endif 