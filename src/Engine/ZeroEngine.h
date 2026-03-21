//
// Created by Terrarizer on 21/01/2026.
//

#ifndef SESSIONZERO_ZEROENGINE_H
#define SESSIONZERO_ZEROENGINE_H
#include <memory>

#include "Core/Input/IInput.h"
#include "Renderer/IRenderer.h"
#include "States/StateManager.h"
#include "Window/IWindow.h"
#include "UI/UIManager.h"

class ZeroEngine {
    std::unique_ptr<IWindow> window;
    std::unique_ptr<IRenderer> renderer;
    std::unique_ptr<IInput> input;
    StateManager stateManager;
    UIManager uiManager;
public:
    // Default width and height
    int window_width;
    int window_height;

    // Constructor
    ZeroEngine(int w_width, int w_height) : window_width(w_width), window_height(w_height) {};

    // Destructor
    ~ZeroEngine() {
        uiManager.shutdown();

        if (window) window->shutdown();
    }

    // Main Methods
    bool initialize();
    void run();

    // Non-copyable, non-movable
    ZeroEngine(const ZeroEngine&) = delete;
    ZeroEngine& operator=(const ZeroEngine&) = delete;
    ZeroEngine(ZeroEngine&&) = delete;
    ZeroEngine& operator=(ZeroEngine&&) = delete;
};


#endif //SESSIONZERO_ZEROENGINE_H