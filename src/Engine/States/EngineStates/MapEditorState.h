//
// Created by Terrarizer on 06/03/2026.
//

#ifndef DNDCREATOR_MAPEDITORSTATE_H
#define DNDCREATOR_MAPEDITORSTATE_H
#include <string>
#include <utility>
#include "../IState.h"
#include "../../Core/Project/MapData.h"
#include "../../Core/Project/ProjectInfo.h"

struct MapEditorTab {
    std::string name;
    MapData mapData;
    Camera camera = { {0.0f, 0.0f, 3.0f} };
};

class MapEditorState : public IState {
    // Project
    std::string m_projectPath;
    ProjectInfo m_projectInfo;

    // Scene
    std::vector<MapEditorTab> m_tabs;
    int activeTab = 0;

    dndMath::Vector2 mousePos;

    RenderContext m_renderContext;
public:
    MapEditorState(std::string project_file) : m_projectPath(std::move(project_file)) {}

    bool initialize() override;
    void handleInput(IInput& input) override;
    void update(float deltaTime) override;
    void render(IRenderer* renderer) override;
    void cleanup() const override;

    ~MapEditorState() override;
};


#endif //DNDCREATOR_MAPEDITORSTATE_H