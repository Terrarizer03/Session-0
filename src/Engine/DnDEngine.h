//
// Created by Terrarizer on 21/01/2026.
//

#ifndef DNDCREATOR_DNDENGINE_H
#define DNDCREATOR_DNDENGINE_H
#include <memory>

#include "Renderer/IRenderer.h"
#include "Window/IWindow.h"

class DnDEngine {
    std::unique_ptr<IWindow> window;
    std::unique_ptr<IRenderer> renderer;
public:
    // Constructor
    DnDEngine() = default;

    // Destructor
    ~DnDEngine() {
        if (window) window->shutdown();
    }

    // Main Methods
    bool initialize();
    void run();
};


#endif //DNDCREATOR_DNDENGINE_H