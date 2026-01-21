//
// Created by Terrarizer on 21/01/2026.
//

#include "../Core/DnDEngine.h"
#include "../Window/GLFWWindow/GLFWWindow.h"

bool DnDEngine::Initialize() {
    window = std::make_unique<GLFWWindow>();

    int window_width = 800;
    int window_height = 600;

    if (!window || !window->initialize() || !window->createWindow(window_width, window_height, "D&D Creator"))
        return false;

    return true;
}

bool DnDEngine::Run() {
    while (!window->shouldClose()) {
        window->pollEvents();
        window->swapBuffers();
    }

    return true;
}

bool DnDEngine::Exit() {
    window->shutdown();

    return true;
}
