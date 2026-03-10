//
// Created by Terrarizer on 10/03/2026.
//

#ifndef DNDCREATOR_IMGUIUI_H
#define DNDCREATOR_IMGUIUI_H
#include "../IUI.h"

class MapEditorUI : public IUI {
public:
    void begin(const std::string& name) override;
    void end() override;
    bool button(const std::string& label) override;
    bool selectable(const std::string& label, bool selected) override;
    void text(const std::string& label) override;
    void separator() override;
    bool beginTabBar(const std::string& id) override;
    bool beginTab(const std::string& label) override;
    void endTab() override;
    void endTabBar() override;
};


#endif //DNDCREATOR_IMGUIUI_H