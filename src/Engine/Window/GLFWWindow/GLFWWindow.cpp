//
// Created by Terrarizer on 21/01/2026.
//

#include <iostream>
#include "glad/glad.h"
#include "GLFWWindow.h"
#include "../../Core/Loaders/EngineSettings.h"

bool GLFWWindow::initialize() {
    if (!glfwInit()) return false;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwSetErrorCallback([](int error, const char* desc) {
        std::cerr << "GLFW Error " << error << ": " << desc << std::endl;
    });

    return true;
}

bool GLFWWindow::setVSync(bool isOn) {
    glfwSwapInterval(isOn ? 1 : 0);
    return isOn;
}

bool GLFWWindow::createWindow(int width, int height, const char* window_name) {
    glfwWindow = glfwCreateWindow(width, height, window_name, nullptr, nullptr);
    if (!glfwWindow) {
        std::cerr << "Failed to create GLFW Window";
        return false;
    }

    glfwMakeContextCurrent(glfwWindow);

    glfwSetFramebufferSizeCallback(glfwWindow, [](GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
        EngineSettings::getInstance().windowWidth = width;
        EngineSettings::getInstance().windowHeight = height;
    });

    return true;
}

bool GLFWWindow::shouldClose() const {
    return glfwWindowShouldClose(glfwWindow) != 0;
}

void GLFWWindow::pollEvents() {
    glfwPollEvents();
}

void GLFWWindow::swapBuffers() {
    glfwSwapBuffers(glfwWindow);
}

bool GLFWWindow::shutdown() {
    glfwTerminate();

    return true;
}