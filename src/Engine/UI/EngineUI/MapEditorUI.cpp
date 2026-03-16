//
// Created by Terrarizer on 10/03/2026.
//

#include "MapEditorUI.h"
#include "../../Core/Loaders/ProjectLoader.h"
#include "../../Core/Loaders/EngineSettings.h"
#include "imgui.h"
#include "../../Core/Project/ProjectDefaults.h"

void MapEditorUI::drawUI(const MapEditorUIContext& ctx) {
    // ==================== Hierarchy ====================
    ImGuiViewport* viewport = ImGui::GetMainViewport();

    // Set position and size before Begin()
    ImGui::SetNextWindowPos(ImVec2(viewport->Pos.x, viewport->Pos.y));
    ImGui::SetNextWindowSize(ImVec2(250, viewport->Size.y));

    ImGui::Begin("Hierarchy", nullptr,
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoBringToFrontOnFocus);

    if (ImGui::Button("Create Map")) {
        ImGui::OpenPopup("New Map");
    }

    if (ImGui::BeginPopupModal("New Map")) {
        static char mapName[128] = "";

        ImGui::Text("Enter Map Name:");
        ImGui::SameLine();
        ImGui::InputText("##MapName", mapName, IM_ARRAYSIZE(mapName));

        if (ImGui::Button("Create Map") && mapName[0] != '\0') {
            ProjectInfo updated = zeroProjectDefaults::createDefaultMap(mapName, ctx.projectPath);
            if (!updated.name.empty()) {
                ctx.projectInfo = updated;
                mapName[0] = '\0';
                ImGui::CloseCurrentPopup();
            }
        }
        if (ImGui::Button("Close")) {
            mapName[0] = '\0';
            ImGui::CloseCurrentPopup();
        }

        ImGui::EndPopup();
    }

    if (ImGui::TreeNode("Maps")) {
        for (const auto &name: ctx.projectInfo.mapPaths | std::views::keys) {
            if (ImGui::TreeNodeEx(name.c_str(), ImGuiTreeNodeFlags_OpenOnArrow)) {
                if (ImGui::IsItemClicked()) {
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
                        float aspect = static_cast<float>(EngineSettings::getInstance().windowWidth - 250) / static_cast<float>(EngineSettings::getInstance().windowHeight);
                        ctx.tabs[newTab].camera.setPerspective(EngineSettings::getInstance().fov, aspect, EngineSettings::getInstance().nearPlane, EngineSettings::getInstance().farPlane);
                    }

                    // Always request the tab switch
                    ctx.requestedTab = name;
                }

                for (auto& tab : ctx.tabs) {
                    if (tab.name == name) {
                        for (auto& obj : tab.mapData.objects) {
                            bool isSelected = (ctx.selectedObjectUUID == obj.UUID);

                            if (ImGui::Selectable(obj.name.c_str(), isSelected)) {
                                ctx.selectedObjectUUID = obj.getUUID();
                            }
                        }
                        break;
                    }
                }
                ImGui::TreePop();
            }
        }
        ImGui::TreePop();
    }

    ImGui::End();

    // ==================== Tabs ====================
    // Set position and size before Begin()
    ImGui::SetNextWindowPos(ImVec2(viewport->Pos.x + 250, viewport->Pos.y));
    ImGui::SetNextWindowSize(ImVec2(viewport->Size.x - 500, 75));

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

                std::string tabLabel = ctx.tabs[i].name + (ctx.tabs[i].mapData.isDirty ? "*" : "");

                if (ImGui::BeginTabItem(tabLabel.c_str(), &ctx.tabs[i].isOpen, flags)) {
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

    // ==================== Properties Panel ====================
    ImGui::SetNextWindowPos(ImVec2(viewport->Size.x - 250, viewport->Pos.y));
    ImGui::SetNextWindowSize(ImVec2(250, viewport->Size.y));

    ImGui::Begin("Properties Panel", nullptr,
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoBringToFrontOnFocus);

    if (!ctx.selectedObjectUUID.empty()) {
        SceneObject* selected = nullptr;

        for (auto& obj : ctx.tabs[ctx.activeTab].mapData.objects) {
            if (obj.getUUID() == ctx.selectedObjectUUID) {
                selected = &obj;
            }
        }

        if (selected) {
            bool changed = false;

            ImGui::Text("Name: %s", selected->name.c_str());
            ImGui::Separator();
            ImGui::Text("Position");
            changed |= ImGui::DragFloat("X##pos", &selected->transform.position.x);
            changed |= ImGui::DragFloat("Y##pos", &selected->transform.position.y);
            changed |= ImGui::DragFloat("Z##pos", &selected->transform.position.z);
            ImGui::Separator();
            ImGui::Text("Rotation");
            changed |= ImGui::DragFloat("X##rot", &selected->transform.rotation.x);
            changed |= ImGui::DragFloat("Y##rot", &selected->transform.rotation.y);
            changed |= ImGui::DragFloat("Z##rot", &selected->transform.rotation.z);
            ImGui::Separator();
            ImGui::Text("Scale");
            changed |= ImGui::DragFloat("X##sca", &selected->transform.scale.x);
            changed |= ImGui::DragFloat("Y##sca", &selected->transform.scale.y);
            changed |= ImGui::DragFloat("Z##sca", &selected->transform.scale.z);

            if (changed) {
                ctx.tabs[ctx.activeTab].mapData.isDirty = true;
            }
        }
    }

    ImGui::End();
}
