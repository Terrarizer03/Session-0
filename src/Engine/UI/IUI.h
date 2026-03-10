//
// Created by Terrarizer on 10/03/2026.
//

#ifndef DNDCREATOR_IUI_H
#define DNDCREATOR_IUI_H
#include <string>

struct IUI {
    virtual ~IUI() = default;
    virtual void begin(const std::string& name) = 0;
    virtual void end() = 0;
    virtual bool button(const std::string& label) = 0;
    virtual bool selectable(const std::string& label, bool selected) = 0;
    virtual void text(const std::string& label) = 0;
    virtual void separator() = 0;
    virtual bool beginTabBar(const std::string& id) = 0;
    virtual bool beginTab(const std::string& label) = 0;
    virtual void endTab() = 0;
    virtual void endTabBar() = 0;
};

#endif //DNDCREATOR_IUI_H