//
// Created by Terrarizer on 04/03/2026.
//

#include "GLShader.h"
#include <iostream>

#include "../../Core/Loaders/AssetLoader.h"

/**
 * Takes in a vertexPath and a fragmentPath, calls the
 * CompileShader function to compile the shader
 * to the GPU.
 * @param vertexPath The file path of the vertex shader
 * @param fragmentPath The file path of the fragment shader
 */
GLShader::GLShader(const char* vertexPath, const char* fragmentPath) {
    const std::string vertexCode = zeroAssetLoader::readFile(vertexPath);
    const std::string fragmentCode = zeroAssetLoader::readFile(fragmentPath);

    if (vertexCode.empty() || fragmentCode.empty()) {
        std::cout << "Failed to load shader files\n";
        m_RendererID = 0;
        return;
    }

    m_RendererID = CompileShader(vertexCode.c_str(), fragmentCode.c_str());
}

void GLShader::bind() const {
    glUseProgram(m_RendererID);
}

void GLShader::unbind() const {
    glUseProgram(0);
}

void GLShader::setUniformMatrix4fv(const std::string& name, const zeroMath::Matrix4& matrix) const {
    GLint location = glGetUniformLocation(m_RendererID, name.c_str());
    if (location == -1) {
        std::cout << "Warning: uniform '" << name << "' not found in shader\n";
        return;
    }
    glUniformMatrix4fv(location, 1, GL_TRUE, matrix.data());
}

void GLShader::setUniformVec3(const std::string& name, const zeroMath::Vector3& vector) const {
    GLint location = glGetUniformLocation(m_RendererID, name.c_str());
    if (location == -1) {
        std::cout << "Warning: uniform '" << name << "' not found\n";
        return;
    }
    glUniform3f(location, vector.x, vector.y, vector.z);
}

void GLShader::setUniformVec4(const std::string& name, const zeroMath::Vector4& vector) const {
    GLint location = glGetUniformLocation(m_RendererID, name.c_str());
    if (location == -1) {
        std::cout << "Warning: uniform '" << name << "' not found\n";
        return;
    }
    glUniform4f(location, vector.x, vector.y, vector.z, vector.w);
}

GLuint GLShader::CompileShader(const char *vertexSrc, const char *fragmentSrc) {
    auto checkShaderCompile = [](const GLuint shader) {
        int success;
        char infoLog[512];
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 512, nullptr, infoLog);
            std::cout << "Shader compilation error:\n" << infoLog << std::endl;
        }
    };

    auto checkProgramLink = [](const GLuint program) {
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

    return program;
}

GLShader::~GLShader() {
    glDeleteProgram(m_RendererID);
}
