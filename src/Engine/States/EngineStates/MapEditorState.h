//
// Created by Terrarizer on 06/03/2026.
//

#ifndef DNDCREATOR_MAPEDITORSTATE_H
#define DNDCREATOR_MAPEDITORSTATE_H
#include <string>
#include <utility>
#include "../IState.h"
#include "../../Core/Rendering Math/ProjectContext.h"

class MapEditorState : public IState {
    // Path
    std::string m_projectPath;

    // Scene
    ProjectContext m_projectContext = {};
    RenderContext m_renderContext = {};

    // Camera
    Camera m_camera = { {0.0f, 0.0f, 3.0f} };

    // Constants
    static constexpr float CAMERA_SPEED = 0.1f;
    static constexpr float SENSITIVITY = 0.1f;
public:
    MapEditorState(std::string project_file) : m_projectPath(std::move(project_file)) {}

    bool initialize() override;
    void handleInput(const IInput& input) override;
    void update(float deltaTime) const override;
    void render(IRenderer* renderer) const override;
    void cleanup() const override;

    ~MapEditorState() override;
};


#endif //DNDCREATOR_MAPEDITORSTATE_H