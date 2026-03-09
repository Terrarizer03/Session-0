//
// Created by Terrarizer on 06/03/2026.
//

#include <iostream>
#include "MapEditorState.h"
#include "../../Renderer/OpenGLRenderer/GLShader.h"
#include "../../Core/Loaders/AssetLoader.h"
#include "../../Core/Loaders/EngineSettings.h"
#include "../../Core/Loaders/ProjectLoader.h"
#include "GLFW/glfw3.h"

bool MapEditorState::initialize() {
    std::cout << "MapEditorState initialized" << std::endl;

    m_projectInfo = dndProjectLoader::loadProject("nothing yet.test");

    // PUSH A DEFAULT TAB
    m_tabs.emplace_back();

    // SET UP THE TAB
    m_tabs[activeTab].mapData = dndProjectLoader::loadMapData(m_projectInfo, "Dungeon");

    // TEST
    float aspect = static_cast<float>(EngineSettings::getInstance().windowWidth) / static_cast<float>(EngineSettings::getInstance().windowHeight);
    m_tabs[activeTab].camera.setPerspective(EngineSettings::getInstance().fov, aspect, EngineSettings::getInstance().nearPlane, EngineSettings::getInstance().farPlane);

    m_renderContext.camera = &m_tabs[activeTab].camera;
    m_renderContext.lightDir = { 0.5f, 1.0f, 0.3f };

    std::cout << m_tabs[activeTab].mapData.objects.size() << "\n";

    return true;
}

void MapEditorState::handleInput(const IInput& input) {
    m_tabs[activeTab].camera.yaw += input.getDeltaX() * SENSITIVITY;
    m_tabs[activeTab].camera.pitch += input.getDeltaY() * SENSITIVITY;

    // Clamp pitch so m_tabs[activeTab].camera doesn't flip upside down
    if (m_tabs[activeTab].camera.pitch > 89.0f) m_tabs[activeTab].camera.pitch = 89.0f;
    if (m_tabs[activeTab].camera.pitch < -89.0f) m_tabs[activeTab].camera.pitch = -89.0f;

    m_tabs[activeTab].camera.updateFront();
    const dndMath::Vector3 side = m_tabs[activeTab].camera.front.cross(m_tabs[activeTab].camera.up).normalized();

    if (input.getKey(GLFW_KEY_W))
        m_tabs[activeTab].camera.position += m_tabs[activeTab].camera.front * CAMERA_SPEED;
    if (input.getKey(GLFW_KEY_S))
        m_tabs[activeTab].camera.position -= m_tabs[activeTab].camera.front * CAMERA_SPEED;
    if (input.getKey(GLFW_KEY_A))
        m_tabs[activeTab].camera.position -= side * CAMERA_SPEED;
    if (input.getKey(GLFW_KEY_D))
        m_tabs[activeTab].camera.position += side * CAMERA_SPEED;
    if (input.getKey(GLFW_KEY_Q))
        m_tabs[activeTab].camera.position -= m_tabs[activeTab].camera.up * CAMERA_SPEED;
    if (input.getKey(GLFW_KEY_E))
        m_tabs[activeTab].camera.position += m_tabs[activeTab].camera.up * CAMERA_SPEED;
}

void MapEditorState::update(float deltaTime) const {

}

void MapEditorState::render(IRenderer* renderer) const {
    for (const SceneObject& object : m_tabs[activeTab].mapData.objects) {
        renderer->draw(*object.mesh, object.transform, object.material, m_renderContext);
    }
}

void MapEditorState::cleanup() const {

}

MapEditorState::~MapEditorState() {
    MapEditorState::cleanup();
}

