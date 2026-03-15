//
// Created by Terrarizer on 06/03/2026.
//

#ifndef SESSIONZERO_MAPEDITORSTATE_H
#define SESSIONZERO_MAPEDITORSTATE_H
#include <string>
#include <utility>
#include "../IState.h"
#include "../../Core/Project/ProjectInfo.h"
#include "../../UI/EngineUI/MapEditorUI.h"
#include "MapEditorTab.h"

class MapEditorState : public IState {
    // Project
    std::string m_projectPath;
    ProjectInfo m_projectInfo = {};

    // Scene
    bool cursorLocked = false;
    std::vector<MapEditorTab> m_tabs = {};
    int activeTab = 0;
    int m_selectedObjectIndex = -1;
    std::string m_requestedTab;

    MapEditorUI m_mapEditorUI;

    zeroMath::Vector2 mousePos = {};

    RenderContext m_renderContext = {};
public:
    MapEditorState(std::string project_file) : m_projectPath(std::move(project_file)) {}

    bool initialize() override;
    void handleInput(IInput& input) override;
    void update(float deltaTime) override;
    void render(IRenderer* renderer) override;
    void cleanup() const override;

    ~MapEditorState() override;
};


#endif //SESSIONZERO_MAPEDITORSTATE_H