//
// Created by Terrarizer on 21/01/2026.
//

#ifndef DNDCREATOR_DNDENGINE_H
#define DNDCREATOR_DNDENGINE_H
#include <memory>

#include "Core/Input/IInput.h"
#include "Renderer/IRenderer.h"
#include "Window/IWindow.h"

class DnDEngine {
    std::unique_ptr<IWindow> window;
    std::unique_ptr<IRenderer> renderer;
    std::unique_ptr<IInput> input;
public:
    int window_width = 800;
    int window_height = 800;

    // Constructor
    DnDEngine(int w_width, int w_height) : window_width(w_width), window_height(w_height) {};

    // Destructor
    ~DnDEngine() {
        if (window) window->shutdown();
    }

    // Main Methods
    bool initialize();
    void run() const;
};


#endif //DNDCREATOR_DNDENGINE_H