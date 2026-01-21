//
// Created by Terrarizer on 21/01/2026.
//

#include <iostream>
#include "GLFWWindow.h"

bool GLFWWindow::initialize() {
    if (!glfwInit()) return false;

    return true;
}

bool GLFWWindow::createWindow(int width, int height, const char* window_name) {
    glfwWindow = glfwCreateWindow(width, height, window_name, nullptr, nullptr);
    if (!glfwWindow) {
        std::cerr << "Failed to create GLFW Window";
        return false;
    }

    glfwMakeContextCurrent(glfwWindow.value());

    return true;
}

bool GLFWWindow::shouldClose() const {
    return glfwWindowShouldClose(glfwWindow.value()) != 0;
}

void GLFWWindow::pollEvents() {
    glfwPollEvents();
}

void GLFWWindow::swapBuffers() {
    glfwSwapBuffers(glfwWindow.value());
}

bool GLFWWindow::shutdown() {
    glfwTerminate();

    return true;
}
