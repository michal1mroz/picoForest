#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>

void errCallback(int error, const char* description){
    std::cerr << "GLFW Error: "<< description <<std::endl;
}

GLFWwindow *create_window() {
    glfwSetErrorCallback(errCallback);

    if(!glfwInit()){
        std::cerr << "Failed to initialize GLFW" <<std::endl;
        exit(-1);
    }

    GLFWwindow* window = glfwCreateWindow(640, 480, "OpenGL Test", NULL, NULL);
    if(!window){
        std::cerr << "Failed to create GLFW window" <<std::endl;
        glfwTerminate();
        exit(-1);
    }
    glfwMakeContextCurrent(window);
    glewInit();
    return window;
}

float vertices[] = {
    -1.0f, -1.0f, -1.0f,
    -1.0f, 1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, 1.0f, -1.0f,
    -1.0f, -1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, -1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
};

unsigned int indices[] = {
    0, 1, 2,
    1, 2, 3,
    2, 3, 6,
    3, 6, 7,
    1, 3, 5,
    3, 5, 7,
};

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

int main(){
    auto window = create_window();

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


    unsigned int vbo;
    glGenBuffers(1, &vbo);

    unsigned int ebo;
    glGenBuffers(1, &ebo);

    unsigned int vao;
    glGenVertexArrays(1, &vao);


    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), nullptr);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    while(!glfwWindowShouldClose(window)){
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader_program);
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(unsigned int), GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}