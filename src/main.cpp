#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include "kitty/Kitty.h"

void errCallback(int error, const char* description){
    std::cerr << "GLFW Error: "<< description <<std::endl;
}

GLFWwindow *create_window() {
    glfwSetErrorCallback(errCallback);

    if(!glfwInit()){
        std::cerr << "Failed to initialize GLFW" <<std::endl;
        exit(-1);
    }

    GLFWwindow* window = glfwCreateWindow(640, 480, "pico Forest", NULL, NULL);
    if(!window){
        std::cerr << "Failed to create GLFW window" <<std::endl;
        glfwTerminate();
        exit(-1);
    }
    glfwMakeContextCurrent(window);
    glewInit();
    return window;
}

int load_shader(std::string filename, int kind) {
    std::ifstream ifs(filename);
    std::string shader_source(
        (std::istreambuf_iterator<char>(ifs)), 
        std::istreambuf_iterator<char>()
    );

    auto str = shader_source.c_str();

    unsigned int shader = glCreateShader(kind);
    glShaderSource(shader, 1, &str, nullptr);
    glCompileShader(shader);

    int status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

    if(!status) {
        char info[512];
        glGetShaderInfoLog(shader, 512, nullptr, info);
        std::cerr << info << std::endl;
        exit(-1);
    }


    return shader;
}

GLuint shader_program_setup(){
    auto vertex_shader = load_shader("src/shader.vert", GL_VERTEX_SHADER);
    auto fragment_shader = load_shader("src/shader.frag", GL_FRAGMENT_SHADER);
    auto shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);

    int status;
    glGetProgramiv(shader_program, GL_LINK_STATUS, &status);
    if(!status) {
        char info[512];
        glGetProgramInfoLog(shader_program, 512, nullptr, info);
        std::cerr << info << std::endl;
        exit(-1);
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return shader_program;
}


int main(){
    auto window = create_window();
    
    auto shader_program = shader_program_setup();
    
    Kitty cat(shader_program, 2, 2);
    Kitty cat2(shader_program, 0,0);

    while(!glfwWindowShouldClose(window)){
        glClear(GL_COLOR_BUFFER_BIT);

        cat.render(); // somethings fucked up with its rendering
        cat2.render(); 

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteProgram(shader_program);
    glfwTerminate();

    return 0;
}