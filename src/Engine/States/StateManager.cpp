//
// Created by Terrarizer on 06/03/2026.
//

#include "StateManager.h"

void StateManager::pushState(std::unique_ptr<IState> state) {
    state->setStateManager(this);
    m_states.push(std::move(state));
    m_states.top()->initialize();
}

void StateManager::popState() {
    m_states.top()->cleanup();
    m_states.pop();
}

void StateManager::changeState(std::unique_ptr<IState> state) {
    if (!m_states.empty()) popState();
    pushState(std::move(state));
}

IState* StateManager::getCurrentState() {
    return m_states.top().get();
}

void StateManager::handleInput(IInput& input) {
    if (!m_states.empty())
        m_states.top()->handleInput(input);
}

void StateManager::update(float deltaTime) {
    if (!m_states.empty())
        m_states.top()->update(deltaTime);
}

void StateManager::render(IRenderer* renderer) {
    if (!m_states.empty())
        m_states.top()->render(renderer);
}