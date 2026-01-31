//
// Created by Terrarizer on 21/01/2026.
//

#include <iostream>
#include "DnDEngine.h"

#include <cmath>

#include "glad/glad.h"
#include "Renderer/OpenGLRenderer/GLRenderer.h"
#include "Window/GLFWWindow/GLFWWindow.h"

bool DnDEngine::Initialize() {
    int window_width = 800;
    int window_height = 600;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = std::make_unique<GLFWWindow>();
    if (!window || !window->initialize() || !window->createWindow(window_width, window_height, "D&D Creator")) {
        std::cout << "Failed to initialize window \n";
        return false;
    }

    window->setVSync(true); // For now, stick with this as true

    renderer = std::make_unique<GLRenderer>();
    if (!renderer || !renderer->initialize()) {
        std::cout << "Failed to initialize renderer \n";
        return false;
    }

    renderer->setViewport(0, 0, 800, 800);

    return true;
}

// test ---------------

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";

// test ---------------

void DnDEngine::Run() {

    // Test ----------------------------
    float h = std::sqrt(3.0f) / 2.0f; // height of equilateral triangle

    float vertices[] = {
        -0.5f, -h / 3.0f, 0.0f,   // left vertex
         0.5f, -h / 3.0f, 0.0f,   // right vertex
         0.0f,  2.0f * h / 3.0f, 0.0f, // top vertex
    };


    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    GLuint program = glCreateProgram();

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    GLuint VAO, VBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(vertices),
        vertices,
        GL_STATIC_DRAW
    );

    glVertexAttribPointer(
    0,              // location in shader
    3,              // vec3
    GL_FLOAT,
    GL_FALSE,
    3 * sizeof(float),
    (void*)0
    );
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    auto checkShaderCompile = [](GLuint shader) {
        int success;
        char infoLog[512];
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 512, NULL, infoLog);
            std::cout << "Shader compilation error:\n" << infoLog << std::endl;
        }
    };

    checkShaderCompile(vertexShader);
    checkShaderCompile(fragmentShader);

    int linkSuccess;
    char linkInfo[512];
    glGetProgramiv(program, GL_LINK_STATUS, &linkSuccess);
    if (!linkSuccess) {
        glGetProgramInfoLog(program, 512, NULL, linkInfo);
        std::cout << "Shader linking error:\n" << linkInfo << std::endl;
    }

    // Test ----------------------------

    while (!window->shouldClose()) {
        renderer->clearColor(0.07f, 0.13f, 0.17f, 1.0f);

        glUseProgram(program);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        window->pollEvents();
        window->swapBuffers();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(program);
}
