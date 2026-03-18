//
// Created by Terrarizer on 06/03/2026.
//

#include <iostream>
#include "MapEditorState.h"

#include "ProjectManagerState.h"
#include "../StateManager.h"
#include "../../Renderer/OpenGLRenderer/GLShader.h"
#include "../../Core/Utilities/constants.h"
#include "../../Core/Loaders/EngineSettings.h"
#include "../../Core/Loaders/ProjectLoader.h"
#include "GLFW/glfw3.h"

bool MapEditorState::initialize() {
    std::cout << "MapEditorState initialized in project " << m_projectPath << std::endl;

    m_projectInfo = zeroProjectLoader::loadProject(m_projectPath);

    m_renderContext.lightDir = { 0.5f, 1.0f, 0.3f };

    return true;
}

void MapEditorState::handleInput(IInput& input) {
    if (!m_tabs.empty()) {
        if (input.getMouseButton(GLFW_MOUSE_BUTTON_RIGHT)) {
            if (!cursorLocked) {
                input.setCursorMode(true);
                input.resetMouseDelta(); // Finally fixed that jumpy ass shit, just had to reset the mouse delta
                cursorLocked = true;
            }
            m_tabs[activeTab].camera.yaw += input.getDeltaX() * zeroConstants::SENSITIVITY;
            m_tabs[activeTab].camera.pitch += input.getDeltaY() * zeroConstants::SENSITIVITY;
        } else {
            if (cursorLocked) {
                input.setCursorMode(false);
                cursorLocked = false;
            }
        }

        // Clamp pitch so m_tabs[activeTab].camera doesn't flip upside down
        if (m_tabs[activeTab].camera.pitch > 89.0f) m_tabs[activeTab].camera.pitch = 89.0f;
        if (m_tabs[activeTab].camera.pitch < -89.0f) m_tabs[activeTab].camera.pitch = -89.0f;

        m_tabs[activeTab].camera.updateFront();
        const zeroMath::Vector3 side = m_tabs[activeTab].camera.front.cross(m_tabs[activeTab].camera.up).normalized();

        if (input.getKey(GLFW_KEY_LEFT_CONTROL) && input.getKeyPressed(GLFW_KEY_S)) {
            zeroProjectLoader::saveMapData(m_tabs[activeTab].mapData, m_projectPath, m_tabs[activeTab].name);
        }

        if (input.getKey(GLFW_KEY_W))
            m_tabs[activeTab].camera.position += m_tabs[activeTab].camera.front * zeroConstants::CAMERA_SPEED;
        if (input.getKey(GLFW_KEY_S))
            m_tabs[activeTab].camera.position -= m_tabs[activeTab].camera.front * zeroConstants::CAMERA_SPEED;
        if (input.getKey(GLFW_KEY_A))
            m_tabs[activeTab].camera.position -= side * zeroConstants::CAMERA_SPEED;
        if (input.getKey(GLFW_KEY_D))
            m_tabs[activeTab].camera.position += side * zeroConstants::CAMERA_SPEED;
        if (input.getKey(GLFW_KEY_Q))
            m_tabs[activeTab].camera.position -= m_tabs[activeTab].camera.up * zeroConstants::CAMERA_SPEED;
        if (input.getKey(GLFW_KEY_E))
            m_tabs[activeTab].camera.position += m_tabs[activeTab].camera.up * zeroConstants::CAMERA_SPEED;
    }
}

void MapEditorState::update(float deltaTime) {

}

void MapEditorState::render(IRenderer* renderer) {
    renderer->setViewport(250, 0 , EngineSettings::getInstance().windowWidth - 500, EngineSettings::getInstance().windowHeight - 75);
    renderer->setRenderMode(EngineSettings::getInstance().debugMode ?
                           RenderMode::WIREFRAME : RenderMode::SOLID);

    if (!m_tabs.empty()) {
        m_renderContext.camera = &m_tabs[activeTab].camera;
        for (const SceneObject& object : m_tabs[activeTab].mapData.objects) {
            renderer->draw(*object.mesh, object.transform, object.material, m_renderContext);
        }
    }
    MapEditorUIContext ctx(m_projectInfo, m_tabs, m_renderContext, activeTab, m_selectedObjectUUID,m_requestedTab, m_projectPath);
    m_mapEditorUI.drawUI(ctx);
    if (m_mapEditorUI.request.requestChange) {
        stateManager->requestStateChange(std::make_unique<ProjectManagerState>());
    }
}

void MapEditorState::cleanup() const {

}

MapEditorState::~MapEditorState() {
    MapEditorState::cleanup();
}

