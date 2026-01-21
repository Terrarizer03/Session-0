//
// Created by Terrarizer on 21/01/2026.
//

#ifndef DNDCREATOR_DNDENGINE_H
#define DNDCREATOR_DNDENGINE_H
#include <memory>
#include "../Window/IWindow.h"

class DnDEngine {
    std::unique_ptr<IWindow> window;
public:
    // Constructor
    DnDEngine() = default;

    // Destructor
    ~DnDEngine() = default;

    // Main Methods
    bool Initialize();
    bool Run();
    bool Exit();
};


#endif //DNDCREATOR_DNDENGINE_H