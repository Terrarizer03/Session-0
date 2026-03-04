//
// Created by Terrarizer on 04/03/2026.
//

#include "GLShader.h"
#include <iostream>

GLShader::GLShader(const char* vertexSrc, const char* fragmentSrc) {
    auto checkShaderCompile = [](GLuint shader) {
        int success;
        char infoLog[512];
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 512, nullptr, infoLog);
            std::cout << "Shader compilation error:\n" << infoLog << std::endl;
        }
    };

    auto checkProgramLink = [](GLuint program) {
        int linkSuccess;
        char linkInfo[512];
        glGetProgramiv(program, GL_LINK_STATUS, &linkSuccess);
        if (!linkSuccess) {
            glGetProgramInfoLog(program, 512, nullptr, linkInfo);
            std::cout << "Shader linking error:\n" << linkInfo << std::endl;
        }
    };

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSrc, nullptr);
    glCompileShader(vertexShader);
    checkShaderCompile(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSrc, nullptr);
    glCompileShader(fragmentShader);
    checkShaderCompile(fragmentShader);

    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    checkProgramLink(program);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    m_RendererID = program;
}

void GLShader::Bind() const {
    glUseProgram(m_RendererID);
}

void GLShader::Unbind() const {
    glUseProgram(0);
}

void GLShader::SetUniform(const std::string&, const dndMath::Matrix4& matrix) {

}

void GLShader::CompileShader(const char &vertexSrc, const char &fragmentSrc) {

}

GLShader::~GLShader() {
    glDeleteProgram(m_RendererID);
}
