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

class Kitty{
public:
    Kitty(unsigned int shaderProgram, int posX, int posY) : shaderProgram(shaderProgram){
        this->load_vertices_kitty(posX, posY);
        this->buffer_setup();
    }

    void render(){
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, sizeof(index)/sizeof(unsigned int), GL_UNSIGNED_INT, 0);
    }

private:
    float vert[sizeof(vertices)/sizeof(vertices[0])];
    unsigned int index[sizeof(indices)/sizeof(indices[0])];
    unsigned int VBO, EBO, VAO;
    unsigned int shaderProgram;

    void load_vertices_kitty(int x, int y){
        int vertCount = sizeof(vertices)/sizeof(vertices[0]);
        for(int i = 0; i < vertCount; i+=3){
            this->vert[i] = vertices[i] + x;
            this->vert[i+1] = vertices[i+1] + y;
            this->vert[i+2] = vertices[i+2];
        }
        std::copy(std::begin(indices), std::end(indices), std::begin(index));
    }

    void buffer_setup(){
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
};



int main(){
    auto window = create_window();
    
    auto shader_program = shader_program_setup();
    
    Kitty cat(shader_program, 2, 2);
    Kitty cat2(shader_program, 0,0);

    while(!glfwWindowShouldClose(window)){
        glClear(GL_COLOR_BUFFER_BIT);

        cat.render();
        cat2.render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }



    glDeleteProgram(shader_program);
    glfwTerminate();

    return 0;
}