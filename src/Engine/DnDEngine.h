//
// Created by Terrarizer on 21/01/2026.
//

#ifndef DNDCREATOR_DNDENGINE_H
#define DNDCREATOR_DNDENGINE_H
#include <memory>

#include "Core/Input/IInput.h"
#include "Renderer/IRenderer.h"
#include "States/StateManager.h"
#include "Window/IWindow.h"

class DnDEngine {
    std::unique_ptr<IWindow> window;
    std::unique_ptr<IRenderer> renderer;
    std::unique_ptr<IInput> input;
    StateManager stateManager;
public:
    // Default width and height
    int window_width;
    int window_height;

    // Constructor
    DnDEngine(int w_width, int w_height) : window_width(w_width), window_height(w_height) {};

    // Destructor
    ~DnDEngine() {
        if (window) window->shutdown();
    }

    // Main Methods
    bool initialize();
    void run();

    // Non-copyable, non-movable
    DnDEngine(const DnDEngine&) = delete;
    DnDEngine& operator=(const DnDEngine&) = delete;
    DnDEngine(DnDEngine&&) = delete;
    DnDEngine& operator=(DnDEngine&&) = delete;
};


#endif //DNDCREATOR_DNDENGINE_H