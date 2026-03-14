//
// Created by Terrarizer on 06/03/2026.
//

#include <filesystem>
#include <iostream>
#include "ProjectManagerState.h"

#include <chrono>

#include "imgui.h"
#include "MapEditorState.h"
#include "../StateManager.h"


bool ProjectManagerState::initialize() {
    try {
        for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(EngineSettings::getInstance().projectPath)) {
            if (!zeroProjectLoader::isValidProject(entry.path().string())) continue; // Example: entry.path().string() = "C:/Users/NICO/Documents/D&D Creator/Projects/default_campaign.dnd"

            ProjectData projectData;
            projectData.path = entry.path().string();
            projectData.projectInfo = zeroProjectLoader::loadProject(entry.path().string());

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
    // ================== TEMPORARY IMGUI CODE ==================
    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);

    ImGui::Begin("Project Manager", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
    ImGui::Text("Projects found: %d", static_cast<int>(m_project_paths.size()));
    ImGui::SameLine();
    if (ImGui::Button("New Project")) {
        ImGui::OpenPopup("New Project");
    }

    if (ImGui::BeginPopupModal("New Project")) {
        static char projectName[128] = "";
        static char author[128] = "";

        ImGui::Text("Project Name:");
        ImGui::SameLine();
        ImGui::InputText("##ProjectName", projectName, 128);
        ImGui::Text("Author Name:");
        ImGui::SameLine();
        ImGui::InputText("##AuthorName", author, IM_ARRAYSIZE(author));

        if (ImGui::Button("Create New Project")) {
            std::string path = zeroProjectLoader::createProject(projectName, author);
            projectName[0] = '\0';
            author[0] = '\0';
            stateManager->requestStateChange(std::make_unique<MapEditorState>(path));
        }

        if (ImGui::Button("Close")) {
            ImGui::CloseCurrentPopup();
        }

        ImGui::EndPopup();
    }

    for (const ProjectData& project : m_project_paths) {
        ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.2f, 0.2f, 0.2f, 1.0f));
        ImGui::SetNextWindowSize({250.0f, 150.0f});
        ImGui::BeginChild(project.projectInfo.name.c_str(), ImVec2(0, 0), false);

        ImGui::Text("Project Name: %s", project.projectInfo.name.c_str());
        ImGui::Text("Author: %s", project.projectInfo.author.c_str());
        ImGui::Text("Version: %s", project.projectInfo.version.c_str());
        ImGui::Text("Time Created: %s", project.projectInfo.timeCreated.c_str());
        ImGui::Separator();

        if (ImGui::Button("Open")) {
            // TODO: Not sure why this won't work, but that doesn't concern me tonight. Fuck this
            // auto now = std::chrono::system_clock::now();
            // auto today = std::chrono::year_month_day{std::chrono::floor<std::chrono::days>(now)};
            //
            // std::string dateStr = std::format("{}-{:02}-{:02}",
            //                           static_cast<int>(today.year()),
            //                           static_cast<unsigned>(today.month()),
            //                           static_cast<unsigned>(today.day())
            //                       );
            // project.projectInfo.timeModified = dateStr;
            stateManager->requestStateChange(std::make_unique<MapEditorState>(project.path));
        }

        ImGui::EndChild();
        ImGui::PopStyleColor();
    }
    ImGui::End();
    // ================== TEMPORARY IMGUI CODE ==================
}

void ProjectManagerState::cleanup() const {

}

ProjectManagerState::~ProjectManagerState() = default;