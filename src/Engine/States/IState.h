//
// Created by Terrarizer on 06/03/2026.
//

#ifndef SESSIONZERO_ISTATE_H
#define SESSIONZERO_ISTATE_H
#include "../Core/Input/IInput.h"
#include "../Renderer/IRenderer.h"

class StateManager;

class IState {
protected:
    StateManager* stateManager = nullptr;
public:
    virtual ~IState() = default;
    virtual bool initialize() = 0;
    virtual void handleInput(IInput& input) = 0;
    virtual void update(float deltaTime) = 0;
    virtual void render(IRenderer* renderer) = 0;
    virtual void cleanup() const = 0;

    void setStateManager(StateManager* _stateManager) { this->stateManager = _stateManager; }
};

#endif //SESSIONZERO_ISTATE_H