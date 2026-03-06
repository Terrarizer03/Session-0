//
// Created by Terrarizer on 06/03/2026.
//

#ifndef DNDCREATOR_MAPEDITORSTATE_H
#define DNDCREATOR_MAPEDITORSTATE_H
#include <string>

#include "../IState.h"

class MapEditorState : public IState {
protected:
    std::string& project_file;
public:
    explicit MapEditorState(StateManager* stateManager, std::string& _project_file) : project_file(_project_file) {
        setStateManager(stateManager);
    }

    bool initialize() override;
    void handleInput(const IInput& input) override;
    void update(float deltaTime) const override;
    void render() const override;
    void cleanup() const override;

    ~MapEditorState() override;
};


#endif //DNDCREATOR_MAPEDITORSTATE_H