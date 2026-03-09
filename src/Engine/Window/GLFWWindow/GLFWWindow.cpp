//
// Created by Terrarizer on 21/01/2026.
//

#include <iostream>
#include "GLFWWindow.h"

bool GLFWWindow::initialize() {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    if (!glfwInit()) return false;

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