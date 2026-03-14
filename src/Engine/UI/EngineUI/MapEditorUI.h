//
// Created by Terrarizer on 10/03/2026.
//

#ifndef DNDCREATOR_IMGUIUI_H
#define DNDCREATOR_IMGUIUI_H
#include <string>
#include <vector>
#include "../../States/EngineStates/MapEditorTab.h"
#include "../../Core/RenderingMath/RenderContext.h"
#include "../../Core/Project/ProjectInfo.h"

struct MapEditorUIContext {
    ProjectInfo& projectInfo;
    std::vector<MapEditorTab>& tabs;
    RenderContext& renderContext;
    int& activeTab;
    std::string& requestedTab;

    MapEditorUIContext(ProjectInfo& _projectInfo, std::vector<MapEditorTab>& _tabs, RenderContext& _renderContext, int& _activeTab, std::string& _requestedTab)
        : projectInfo(_projectInfo), tabs(_tabs), renderContext(_renderContext), activeTab(_activeTab), requestedTab(_requestedTab) {
    }
};

struct MapEditorUI {
    void drawUI(MapEditorUIContext& ctx);
};


#endif //DNDCREATOR_IMGUIUI_H