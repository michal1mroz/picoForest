#ifndef KITTY_H
#define KITTY_H

#include "../RawObject.h"

class Kitty : public RawObject {
private:
    static float vertices[];
    static unsigned int indices[];

public:
    Kitty(unsigned int shaderProgram, int posX, int posY);

    virtual void render() override;
};

#endif