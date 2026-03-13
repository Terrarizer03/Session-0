//
// Created by Terrarizer on 06/03/2026.
//

#include <iostream>
#include "MapEditorState.h"
#include "../../Renderer/OpenGLRenderer/GLShader.h"
#include "../../Core/Utilities/constants.h"
#include "../../Core/Loaders/EngineSettings.h"
#include "../../Core/Loaders/ProjectLoader.h"
#include "GLFW/glfw3.h"
#include "imgui.h"

bool MapEditorState::initialize() {
    std::cout << "MapEditorState initialized in project " << m_projectPath << std::endl;

    m_projectInfo = dndProjectLoader::loadProject(m_projectPath);

    // SET UP THE TABS
    // TODO: ADD LAZY LOADING
    int tabIndex = 0;
    for (const auto& pair : m_projectInfo.mapPaths) {
        std::cout << "Name: " << pair.first << " Path: " << pair.second << "\n";
        m_tabs.emplace_back();
        m_tabs[tabIndex].name = pair.first;
        m_tabs[tabIndex].mapData = dndProjectLoader::loadMapData(m_projectInfo, pair.first);

        float aspect = static_cast<float>(EngineSettings::getInstance().windowWidth) / static_cast<float>(EngineSettings::getInstance().windowHeight);
        m_tabs[tabIndex].camera.setPerspective(EngineSettings::getInstance().fov, aspect, EngineSettings::getInstance().nearPlane, EngineSettings::getInstance().farPlane);

        std::cout << m_tabs[tabIndex].mapData.objects.size() << "\n";

        tabIndex++;
    }

    m_renderContext.lightDir = { 0.5f, 1.0f, 0.3f };

    return true;
}

void MapEditorState::handleInput(IInput& input) {
    // TODO: Not sure if the fix worked or anything but it's still pretty jumpy
    if (input.getMouseButton(GLFW_MOUSE_BUTTON_RIGHT)) {
        if (!cursorLocked) {
            input.setCursorMode(true);
            cursorLocked = true;
        }
        m_tabs[activeTab].camera.yaw += input.getDeltaX() * dndConstants::SENSITIVITY;
        m_tabs[activeTab].camera.pitch += input.getDeltaY() * dndConstants::SENSITIVITY;
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
    const dndMath::Vector3 side = m_tabs[activeTab].camera.front.cross(m_tabs[activeTab].camera.up).normalized();

    if (input.getKey(GLFW_KEY_W))
        m_tabs[activeTab].camera.position += m_tabs[activeTab].camera.front * dndConstants::CAMERA_SPEED;
    if (input.getKey(GLFW_KEY_S))
        m_tabs[activeTab].camera.position -= m_tabs[activeTab].camera.front * dndConstants::CAMERA_SPEED;
    if (input.getKey(GLFW_KEY_A))
        m_tabs[activeTab].camera.position -= side * dndConstants::CAMERA_SPEED;
    if (input.getKey(GLFW_KEY_D))
        m_tabs[activeTab].camera.position += side * dndConstants::CAMERA_SPEED;
    if (input.getKey(GLFW_KEY_Q))
        m_tabs[activeTab].camera.position -= m_tabs[activeTab].camera.up * dndConstants::CAMERA_SPEED;
    if (input.getKey(GLFW_KEY_E))
        m_tabs[activeTab].camera.position += m_tabs[activeTab].camera.up * dndConstants::CAMERA_SPEED;
}

void MapEditorState::update(float deltaTime) {

}

void MapEditorState::render(IRenderer* renderer) {
    m_renderContext.camera = &m_tabs[activeTab].camera;
    for (const SceneObject& object : m_tabs[activeTab].mapData.objects) {
        renderer->draw(*object.mesh, object.transform, object.material, m_renderContext);
    }

    ImGui::Begin("Map Editor");

    if (ImGui::BeginTabBar("MapTabs")) {
        for (size_t i = 0; i < m_tabs.size(); i++) {
            if (ImGui::BeginTabItem(m_tabs[i].name.c_str())) {
                activeTab = static_cast<int>(i);
                ImGui::EndTabItem();
            }
        }
        ImGui::EndTabBar();
    }

    ImGui::End();
}

void MapEditorState::cleanup() const {

}

MapEditorState::~MapEditorState() {
    MapEditorState::cleanup();
}

