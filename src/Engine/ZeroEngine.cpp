//
// Created by Terrarizer on 21/01/2026.
//

#include <iostream>
#include "ZeroEngine.h"
#include "Core/Input/GLFWInput/GLFWInput.h"
#include "Core/Loaders/EngineSettings.h"
#include "Renderer/OpenGLRenderer/GLRenderer.h"
#include "Window/GLFWWindow/GLFWWindow.h"
#include "States/EngineStates/MapEditorState.h"
#include "States/EngineStates/ProjectManagerState.h"

bool ZeroEngine::initialize() {
    std::cout << "Initializing ZeroEngine" << std::endl;

    window = std::make_unique<GLFWWindow>();
    if (!window || !window->initialize() || !window->createWindow(window_width, window_height, "Session-0")) {
        std::cout << "Failed to initialize window \n";
        return false;
    }

    std::cout << "Window Created" << std::endl;

    window->setVSync(EngineSettings::getInstance().vsyncEnabled);

    renderer = std::make_unique<GLRenderer>();
    if (!renderer || !renderer->initialize()) {
        std::cout << "Failed to initialize renderer \n";
        return false;
    }

    std::cout << "Renderer Created" << std::endl;

    renderer->clearColor(0.07f, 0.13f, 0.17f, 1.0f);
    renderer->setViewport(0, 0, window_width, window_height);

    GLFWwindow* handle = window->getHandle();

    if (!handle) {
        std::cout << "Failed to get window handle" << std::endl;
        return false;
    }

    input = std::make_unique<GLFWInput>(handle);
    uiManager.initialize(handle);

    std::cout << "ImGui Intialized" << std::endl;

    stateManager.pushState(std::make_unique<ProjectManagerState>());

    std::cout << "State Pushed" << std::endl;

    return true;
}

void ZeroEngine::run() {
    double lastTime = glfwGetTime();
    while (!window->shouldClose()) {
        double currentTime = glfwGetTime();
        auto deltaTime = static_cast<float>(currentTime - lastTime);

        IState* state = stateManager.getCurrentState();
        if (!state) return;
        renderer->beginFrame();

        input->update();

        uiManager.beginFrame();

        state->handleInput(*input);
        state->update(deltaTime); // Don't mind this magic number, it's not really needed yet, I just needed to pass in a value
        state->render(renderer.get());

        stateManager.applyPendingState();

        uiManager.endFrame();

        window->pollEvents();
        window->swapBuffers();
    }
}
