#ifndef KITTY_H
#define KITTY_H

#include <GL/glew.h>
#include <iostream>

class Kitty {
private:
    float vert[48]; // hard coded but what about it
    unsigned int index[30];
    unsigned int VBO, EBO, VAO;
    unsigned int shaderProgram;

    void load_vertices_kitty(int x, int y);
    void buffer_setup();
public:
    Kitty(unsigned int shaderProgram, int posX, int posY);
    void render();
};

#endif