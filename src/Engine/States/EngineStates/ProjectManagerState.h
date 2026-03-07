//
// Created by Terrarizer on 06/03/2026.
//

#ifndef DNDCREATOR_PROJECTMANAGERSTATE_H
#define DNDCREATOR_PROJECTMANAGERSTATE_H
#include "../IState.h"


class ProjectManagerState : public IState {
    std::vector<std::string> m_project_paths;
public:
    bool initialize() override;
    void handleInput(const IInput& input) override;
    void update(float deltaTime) const override;
    void render(IRenderer* renderer) const override;
    void cleanup() const override;

    ~ProjectManagerState() override;
};


#endif //DNDCREATOR_PROJECTMANAGERSTATE_H