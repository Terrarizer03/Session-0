//
// Created by Terrarizer on 21/01/2026.
//

#include <iostream>
#include "glad/glad.h"
#include "DnDEngine.h"
#include "Core/Input/GLFWInput/GLFWInput.h"
#include "Core/Loaders/Loader.h"
#include "Core/Nodes/Camera.h"
#include "Core/Rendering Math/Mesh/Mesh.h"
#include "Renderer/OpenGLRenderer/GLRenderer.h"
#include "Window/GLFWWindow/GLFWWindow.h"
#include "Renderer/OpenGLRenderer/GLShader.h"
#include "States/EngineStates/MapEditorState.h"

bool DnDEngine::initialize() {

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

    GLFWwindow* handle = static_cast<GLFWWindow*>(window.get())->getHandle();
    input = std::make_unique<GLFWInput>(handle);

    glfwSetInputMode(handle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glEnable(GL_DEPTH_TEST);

    renderer->setViewport(0, 0, window_width, window_height);

    stateManager.pushState(std::make_unique<MapEditorState>("test_project_file_path"));

    return true;
}

void DnDEngine::run() {
    while (!window->shouldClose()) {
        IState* state = stateManager.getCurrentState();
        if (!state) return;
        renderer->clearColor(0.07f, 0.13f, 0.17f, 1.0f);

        input->update();

        state->handleInput(*input);
        state->update(16.66f);
        state->render(renderer.get());

        window->pollEvents();
        window->swapBuffers();
    }
}
