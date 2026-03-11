//
// Created by Terrarizer on 06/03/2026.
//

#include <filesystem>
#include <iostream>
#include "ProjectManagerState.h"
#include "imgui.h"
#include "MapEditorState.h"
#include "../StateManager.h"


bool ProjectManagerState::initialize() {
    try {
        for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(EngineSettings::getInstance().projectPath)) {
            std::cout << entry.path().string() << std::endl;
            if (!dndProjectLoader::isValidProject(entry.path().string())) continue; // Example: entry.path().string() = "C:/Users/NICO/Documents/D&D Creator/Projects/default_campaign.dnd"

            ProjectData projectData;
            projectData.path = entry.path().string();
            projectData.projectInfo = dndProjectLoader::loadProject(entry.path().string());

            m_project_paths.push_back(projectData);
        }
    } catch (const std::filesystem::filesystem_error& ex) {
        std::cerr << "Error accessing directory: " << ex.what() << std::endl;
    }

    return true;
}

void ProjectManagerState::handleInput(IInput& input) {

}

void ProjectManagerState::update(float deltaTime) {

}

void ProjectManagerState::render(IRenderer* renderer) {
    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);

    ImGui::Begin("Project Manager", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
    ImGui::Text("Projects found: %d", static_cast<int>(m_project_paths.size()));

    for (const ProjectData& project : m_project_paths) {
        ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.2f, 0.2f, 0.2f, 1.0f));
        ImGui::SetNextWindowSize({250.0f, 150.0f});
        ImGui::BeginChild(project.projectInfo.name.c_str(), ImVec2(200, 100), true);

        ImGui::Text("Project Name: %s", project.projectInfo.name.c_str());
        ImGui::Text("Author: %s", project.projectInfo.author.c_str());
        ImGui::Text("Version: %s", project.projectInfo.version.c_str());
        ImGui::Text("Time Created: %s", project.projectInfo.timeCreated.c_str());
        ImGui::Separator();

        if (ImGui::Button("Open")) {
            stateManager->requestStateChange(std::make_unique<MapEditorState>(project.path));
        }

        ImGui::EndChild();
        ImGui::PopStyleColor();

        ImGui::SameLine(); // puts next card beside it instead of below
    }
    ImGui::End();
}

void ProjectManagerState::cleanup() const {

}

ProjectManagerState::~ProjectManagerState() = default;