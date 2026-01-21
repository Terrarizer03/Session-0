//
// Created by Terrarizer on 21/01/2026.
//

#include <iostream>
#include "../Core/DnDEngine.h"
#include "../Renderer/OpenGLRenderer/GLRenderer.h"
#include "../Window/GLFWWindow/GLFWWindow.h"

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

    return true;
}

bool DnDEngine::Run() {
    renderer->setViewport(0, 0, 800, 600);

    while (!window->shouldClose()) {
        renderer->clearColor(0.07f, 0.13f, 0.17f, 1.0f);

        renderer->clear();

        window->pollEvents();
        window->swapBuffers();
    }

    return true;
}

bool DnDEngine::Exit() {
    window->shutdown();

    return true;
}
