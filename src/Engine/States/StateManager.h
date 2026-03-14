//
// Created by Terrarizer on 06/03/2026.
//

#ifndef SESSIONZERO_STATEMANAGER_H
#define SESSIONZERO_STATEMANAGER_H
#include <memory>
#include <stack>
#include "IState.h"
#include "../Core/Input/IInput.h"

class StateManager {
    std::stack<std::unique_ptr<IState>> m_states;
    std::unique_ptr<IState> m_pendingState;
public:
    StateManager() = default;

    void pushState(std::unique_ptr<IState> state);
    void popState();
    void changeState(std::unique_ptr<IState> state);

    IState* getCurrentState();

    void handleInput(IInput& input);
    void update(float deltaTime);
    void render(IRenderer* renderer);

    void requestStateChange(std::unique_ptr<IState> state);
    void applyPendingState();
};


#endif //SESSIONZERO_STATEMANAGER_H