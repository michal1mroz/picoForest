#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <iostream>

void errCallback(int error, const char* description){
    std::cerr << "GLFW Error: "<< description <<std::endl;
}

int main(){
    glfwSetErrorCallback(errCallback);

    if(!glfwInit()){
        std::cerr << "Failed to initialize GLFW" <<std::endl;
        return 1;
    }

    GLFWwindow* window = glfwCreateWindow(640, 480, "OpenGL Test", NULL, NULL);
    if(!window){
        std::cerr << "Failed to create GLFW window" <<std::endl;
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(window);

    while(!glfwWindowShouldClose(window)){
        glClear(GL_COLOR_BUFFER_BIT);
        glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 0.0f, -0.5f);
        glVertex2f(-0.5f, -0.5f);

        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex2d(0.5f, -0.5f);

        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex2d(0.0f, 0.5f);

        glEnd();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}