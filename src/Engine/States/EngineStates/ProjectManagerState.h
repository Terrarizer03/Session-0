//
// Created by Terrarizer on 06/03/2026.
//

#ifndef SESSIONZERO_PROJECTMANAGERSTATE_H
#define SESSIONZERO_PROJECTMANAGERSTATE_H
#include "States/IState.h"
#include "Core/Project/ProjectData.h"
#include "UI/EngineUI/ProjectManagerUI.h"

class ProjectManagerState : public IState {
    std::vector<ProjectData> m_project_paths;
    ProjectManagerUI m_projectManagerUI;
public:
    bool initialize() override;
    void handleInput(IInput& input) override;
    void update(float deltaTime) override;
    void render(IRenderer* renderer) override;
    void cleanup() const override;

    ~ProjectManagerState() override;
};


#endif //SESSIONZERO_PROJECTMANAGERSTATE_H