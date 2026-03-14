//
// Created by Terrarizer on 10/03/2026.
//

#include "MapEditorUI.h"
#include "../../Core/Loaders/ProjectLoader.h"
#include "../../Core/Loaders/EngineSettings.h"
#include "imgui.h"

void MapEditorUI::drawUI(MapEditorUIContext& ctx) {
    // ==================== Hierarchy ====================
    ImGuiViewport* viewport = ImGui::GetMainViewport();

    // Set position and size before Begin()
    ImGui::SetNextWindowPos(ImVec2(viewport->Pos.x, viewport->Pos.y));
    ImGui::SetNextWindowSize(ImVec2(200, viewport->Size.y));

    ImGui::Begin("Hierarchy", nullptr,
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoBringToFrontOnFocus);

    if (ImGui::TreeNode("Maps")) {
        for (const auto& [name, path] : ctx.projectInfo.mapPaths) {
            if (ImGui::Selectable(name.c_str())) {
                // Check if tab already exists
                bool tabExists = false;
                for (auto & m_tab : ctx.tabs) {
                    if (m_tab.name == name) {
                        tabExists = true;
                        break;
                    }
                }

                // Only create if it doesn't exist
                if (!tabExists) {
                    ctx.tabs.emplace_back();
                    int newTab = static_cast<int>(ctx.tabs.size() - 1);
                    ctx.tabs[newTab].name = name;
                    ctx.tabs[newTab].mapData = zeroProjectLoader::loadMapData(ctx.projectInfo, name);
                    float aspect = static_cast<float>(EngineSettings::getInstance().windowWidth - 200) / static_cast<float>(EngineSettings::getInstance().windowHeight);
                    ctx.tabs[newTab].camera.setPerspective(EngineSettings::getInstance().fov, aspect, EngineSettings::getInstance().nearPlane, EngineSettings::getInstance().farPlane);
                }

                // Always request the tab switch
                ctx.requestedTab = name;
            }
        }
        ImGui::TreePop();
    }

    ImGui::End();

    // ==================== Tabs ====================
    // Set position and size before Begin()
    ImGui::SetNextWindowPos(ImVec2(viewport->Pos.x + 200, viewport->Pos.y));
    ImGui::SetNextWindowSize(ImVec2(viewport->Size.x - 200, 50));

    ImGui::Begin("Tabs", nullptr,
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoBringToFrontOnFocus);

    if (!ctx.tabs.empty()) {
        if (ImGui::BeginTabBar("MapTabs")) {
            for (size_t i = 0; i < ctx.tabs.size(); i++) {
                ImGuiTabItemFlags flags = 0;
                if (ctx.tabs[i].name == ctx.requestedTab) {
                    flags = ImGuiTabItemFlags_SetSelected;
                    ctx.requestedTab = "";
                }
                if (ImGui::BeginTabItem(ctx.tabs[i].name.c_str(), &ctx.tabs[i].isOpen, flags)) {
                    ctx.activeTab = static_cast<int>(i);
                    ImGui::EndTabItem();
                }
                if (!ctx.tabs[i].isOpen) {
                    ctx.tabs.erase(ctx.tabs.begin() + static_cast<int>(i));
                    i--;
                    if (ctx.tabs.empty()) {
                        ctx.activeTab = 0;
                    }
                    else if (ctx.activeTab >= static_cast<int>(ctx.tabs.size())) {
                        ctx.activeTab = static_cast<int>(ctx.tabs.size()) - 1;
                    }
                }
            }
            ImGui::EndTabBar();
        }
    } else {
        ImGui::Text("No Maps Found. Create a new map to get started.");
    }

    ImGui::End();
}