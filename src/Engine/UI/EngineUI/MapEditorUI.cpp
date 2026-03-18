//
// Created by Terrarizer on 10/03/2026.
//

#include "MapEditorUI.h"
#include "../../Core/Loaders/ProjectLoader.h"
#include "../../Core/Loaders/EngineSettings.h"
#include "../../Core/Project/ProjectDefaults.h"
#include "../../Core/Project/Tools.h"

void MapEditorUI::drawUI(const MapEditorUIContext& ctx) {
    ImGuiViewport* viewport = ImGui::GetMainViewport();
    drawMenuUI(ctx, viewport);
    drawHierarchyUI(ctx, viewport);
    drawPropertiesPanel(ctx, viewport);
    drawTabsUI(ctx, viewport);
}

void MapEditorUI::drawMenuUI(const MapEditorUIContext& ctx, const ImGuiViewport* viewport) {
    ImGui::SetNextWindowPos(ImVec2(viewport->Pos.x, viewport->Pos.y));
    ImGui::SetNextWindowSize(ImVec2(viewport->Size.x, 100.0f));

    ImGui::Begin("Menu Buttons", nullptr,
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoBringToFrontOnFocus);

    if (ImGui::BeginMainMenuBar())
    {
        // ───── File Menu ─────
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Exit Editor"))
            {
                request.requestChange = true;
            }

            ImGui::EndMenu();
        }

        // ───── Settings Menu Item ─────
        if (ImGui::MenuItem("Settings"))
        {
            ImGui::OpenPopup("Settings");
        }

        if (ImGui::BeginPopupModal("Settings", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
        {
            // This kinda does the changes instantly, so maybe make it apparent that changes won't be saved unless you click "Save Changes"
            ImGui::DragFloat("Far Plane",  &EngineSettings::getInstance().farPlane, 0.1f, 0.0f, 10000.0f);
            ImGui::DragFloat("Near Plane", &EngineSettings::getInstance().nearPlane, 0.1f, 0.0f, 100.0f);
            ImGui::Checkbox("Debug Mode", &EngineSettings::getInstance().debugMode);

            if (ImGui::Button("Save Changes", ImVec2(150, 0)))
            {
                EngineSettings::getInstance().save("engineSettings.json");
            }

            ImGui::Separator();


            if (ImGui::Button("Cancel", ImVec2(150, 0)))
            {
                ImGui::CloseCurrentPopup();
            }

            ImGui::EndPopup();
        }


        ImGui::EndMainMenuBar();
    }

    if (ImGui::Button("Add Sphere##S")) {
        if (!ctx.tabs.empty()) {
            zeroTools::addPrimitive(ctx.tabs[ctx.activeTab].mapData, Primitive::SPHERE);
        }
    }

    if (ImGui::Button("Add Cube##C")) {
        if (!ctx.tabs.empty()) {
            zeroTools::addPrimitive(ctx.tabs[ctx.activeTab].mapData, Primitive::CUBE);
        }
    }

    if (ImGui::Button("Add Plane##P")) {
        if (!ctx.tabs.empty()) {
            zeroTools::addPrimitive(ctx.tabs[ctx.activeTab].mapData, Primitive::PLANE);
        }
    }

    ImGui::End();
}

void MapEditorUI::drawHierarchyUI(const MapEditorUIContext &ctx, const ImGuiViewport* viewport) {
    ImGui::SetNextWindowPos(ImVec2(viewport->Pos.x, viewport->Pos.y + 100.0f));
    ImGui::SetNextWindowSize(ImVec2(250.0f, viewport->Size.y));

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
                        for (size_t i = 0; i < tab.mapData.objects.size(); ++i) { // Not sure if this is a good rework, but I'll figure it out :p
                            auto& obj = tab.mapData.objects[i];

                            bool isSelected = (ctx.selectedObjectUUID == obj.UUID);

                            std::string itemLabel = obj.name + "##" + obj.UUID;

                            if (ImGui::Selectable(itemLabel.c_str(), isSelected)) {
                                ctx.selectedObjectUUID = obj.getUUID();
                            }

                            if (ImGui::BeginPopupContextItem()) {
                                if (ImGui::MenuItem("Delete Object")) {
                                    zeroTools::deleteObject(tab.mapData, obj.getUUID());

                                    if (ctx.selectedObjectUUID == obj.getUUID()) {
                                        ctx.selectedObjectUUID.clear();
                                    }
                                }
                                // Add more items later: Duplicate, etc.
                                ImGui::EndPopup();
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
}

void MapEditorUI::drawTabsUI(const MapEditorUIContext &ctx, const ImGuiViewport *viewport) {
    ImGui::SetNextWindowPos(ImVec2(viewport->Pos.x + 250.0f, viewport->Pos.y + 100.0f));
    ImGui::SetNextWindowSize(ImVec2(viewport->Size.x - 500.0f, 75.0f));

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
}

void MapEditorUI::drawPropertiesPanel(const MapEditorUIContext &ctx, const ImGuiViewport *viewport) {
    ImGui::SetNextWindowPos(ImVec2(viewport->Size.x - 250.0f, viewport->Pos.y + 100.0f));
    ImGui::SetNextWindowSize(ImVec2(250.0f, viewport->Size.y));

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
