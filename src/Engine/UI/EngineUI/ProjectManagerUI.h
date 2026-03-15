//
// Created by Terrarizer on 11/03/2026.
//

#ifndef SESSIONZERO_PROJECTMANAGERUI_H
#define SESSIONZERO_PROJECTMANAGERUI_H
#include <vector>
#include "../../Core/Project/ProjectData.h"
#include "../../States/StateManager.h"

struct ProjectManagerUIContext {
    std::vector<ProjectData>& projectPaths;

    ProjectManagerUIContext(std::vector<ProjectData>& _projectPaths)
        : projectPaths(_projectPaths) {}
};

struct RequestChange {
    bool requestChange = false;
    std::string path;
};

struct ProjectManagerUI {
    RequestChange request;

    void drawUI(const ProjectManagerUIContext& ctx);
};


#endif //SESSIONZERO_PROJECTMANAGERUI_H