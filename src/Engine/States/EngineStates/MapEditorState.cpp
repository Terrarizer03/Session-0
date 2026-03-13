//
// Created by Terrarizer on 06/03/2026.
//

#include <iostream>
#include "MapEditorState.h"

#include <ranges>

#include "../../Renderer/OpenGLRenderer/GLShader.h"
#include "../../Core/Utilities/constants.h"
#include "../../Core/Loaders/EngineSettings.h"
#include "../../Core/Loaders/ProjectLoader.h"
#include "GLFW/glfw3.h"
#include "imgui.h"

bool MapEditorState::initialize() {
    std::cout << "MapEditorState initialized in project " << m_projectPath << std::endl;

    m_projectInfo = dndProjectLoader::loadProject(m_projectPath);

    m_renderContext.lightDir = { 0.5f, 1.0f, 0.3f };

    return true;
}

void MapEditorState::handleInput(IInput& input) {
    if (!m_tabs.empty()) {
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

}

void MapEditorState::update(float deltaTime) {

}

void MapEditorState::render(IRenderer* renderer) {
    // TODO: A LOT OF CLEANUP AND BUGS TO FIX
    ImGui::Begin("Hierarchy");

    if (ImGui::TreeNode("Maps")) {
        for (const auto& [name, path] : m_projectInfo.mapPaths) {
            if (ImGui::Selectable(name.c_str())) {
                // If tab exists, then just set active tab to it
                // If tab doesn't exist, then add a new tab and set active tab to it.
                int existingIndex = -1;
                for (size_t i = 0; i < m_tabs.size(); i++) {
                    if (m_tabs[i].name == name) {
                        existingIndex = static_cast<int>(i);
                        break;
                    }
                }

                if (existingIndex != -1) {
                    activeTab = existingIndex;
                } else {
                    m_tabs.emplace_back();

                    int newTab = static_cast<int>(m_tabs.size() - 1);

                    m_tabs[newTab].name = name;
                    m_tabs[newTab].mapData = dndProjectLoader::loadMapData(m_projectInfo, name);

                    float aspect = static_cast<float>(EngineSettings::getInstance().windowWidth) / static_cast<float>(EngineSettings::getInstance().windowHeight);
                    m_tabs[newTab].camera.setPerspective(EngineSettings::getInstance().fov, aspect, EngineSettings::getInstance().nearPlane, EngineSettings::getInstance().farPlane);

                    activeTab = newTab;
                }
            }
        }
        ImGui::TreePop();
    }

    ImGui::End();

    if (!m_tabs.empty()) {
        m_renderContext.camera = &m_tabs[activeTab].camera;
        for (const SceneObject& object : m_tabs[activeTab].mapData.objects) {
            renderer->draw(*object.mesh, object.transform, object.material, m_renderContext);
        }
    }

    ImGui::Begin("Map Editor");

    if (!m_tabs.empty()) {
        if (ImGui::BeginTabBar("MapTabs")) {
            for (size_t i = 0; i < m_tabs.size(); i++) {
                if (ImGui::BeginTabItem(m_tabs[i].name.c_str())) {
                    activeTab = static_cast<int>(i);
                    ImGui::EndTabItem();
                }
            }
            ImGui::EndTabBar();
        }
    } else {
        ImGui::Text("No Maps Found. Create a new map to get started.");
    }

    ImGui::End();
}

void MapEditorState::cleanup() const {

}

MapEditorState::~MapEditorState() {
    MapEditorState::cleanup();
}

