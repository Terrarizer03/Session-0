//
// Created by Terrarizer on 06/03/2026.
//

#include <filesystem>
#include <iostream>
#include "ProjectManagerState.h"
#include "MapEditorState.h"
#include "States/StateManager.h"
#include "Core/Loaders/ProjectLoader.h"
#include "Core/Loaders/EngineSettings.h"

bool ProjectManagerState::initialize() {
    std::cout << "ProjectManagerState initialized" << std::endl;
    try {
        for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(EngineSettings::getInstance().projectPath)) {
            if (!zeroProjectLoader::isValidProject(entry.path().string())) continue; // Example: entry.path().string() = "C:/Users/NICO/Documents/D&D Creator/Projects/default_campaign.zero"

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
    ProjectManagerUIContext ctx(m_project_paths);
    m_projectManagerUI.drawUI(ctx);
    if (m_projectManagerUI.request.requestChange == true) {
        stateManager->requestStateChange(std::make_unique<MapEditorState>(m_projectManagerUI.request.path));
        m_projectManagerUI.request.requestChange = false;
        m_projectManagerUI.request.path.clear();
    }
}

void ProjectManagerState::cleanup() const {

}

ProjectManagerState::~ProjectManagerState() = default;