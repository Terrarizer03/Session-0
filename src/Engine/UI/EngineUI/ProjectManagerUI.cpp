//
// Created by Terrarizer on 11/03/2026.
//

#include "imgui.h"
#include "ProjectManagerUI.h"
#include "../../States/EngineStates/MapEditorState.h"
#include "../../Core/Loaders/ProjectLoader.h"


void ProjectManagerUI::drawUI(const ProjectManagerUIContext& ctx) {
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);

    ImGui::Begin("Project Manager", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
    ImGui::Text("Projects found: %d", static_cast<int>(ctx.projectPaths.size()));
    ImGui::SameLine();
    if (ImGui::Button("New Project")) {
        ImGui::OpenPopup("New Project");
    }

    if (ImGui::BeginPopupModal("New Project")) {
        static char projectName[128] = "";
        static char author[128] = "";

        ImGui::Text("Project Name:");
        ImGui::SameLine();
        ImGui::InputText("##ProjectName", projectName, IM_ARRAYSIZE(projectName));
        ImGui::Text("Author Name:");
        ImGui::SameLine();
        ImGui::InputText("##AuthorName", author, IM_ARRAYSIZE(author));

        if (ImGui::Button("Create New Project")) {
            std::string path = zeroProjectLoader::createProject(projectName, author);
            projectName[0] = '\0';
            author[0] = '\0';
            request.path = path;
            request.requestChange = true;
        }

        if (ImGui::Button("Close")) {
            ImGui::CloseCurrentPopup();
        }

        ImGui::EndPopup();
    }

    for (const ProjectData& project : ctx.projectPaths) {
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
            request.path = project.path;
            request.requestChange = true;
        }

        ImGui::EndChild();
        ImGui::PopStyleColor();
    }
    ImGui::End();
}
