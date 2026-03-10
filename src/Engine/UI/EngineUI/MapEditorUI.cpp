//
// Created by Terrarizer on 10/03/2026.
//

#include "MapEditorUI.h"
#include "imgui.h"

void MapEditorUI::begin(const std::string &name) {
    ImGui::Begin(name.c_str());
}

void MapEditorUI::end() {
    ImGui::End();
}

bool MapEditorUI::button(const std::string& label) {
    return ImGui::Button(label.c_str());
}

bool MapEditorUI::selectable(const std::string &label, bool selected) {
    return ImGui::Selectable(label.c_str(), selected);
}

void MapEditorUI::text(const std::string& label) {
    ImGui::Text(label.c_str());
}

void MapEditorUI::separator() {
    ImGui::Separator();
}

bool MapEditorUI::beginTabBar(const std::string &id) {
    return ImGui::BeginTabBar(id.c_str());
}

bool MapEditorUI::beginTab(const std::string &id) {
    return ImGui::BeginTabItem(id.c_str());
}

void MapEditorUI::endTab() {
    ImGui::EndTabItem();
}

void MapEditorUI::endTabBar() {
    ImGui::EndTabBar();
}
