//
// Created by Terrarizer on 21/01/2026.
//

#ifndef DNDCREATOR_GLFWWINDOW_H
#define DNDCREATOR_GLFWWINDOW_H

#include <optional>
#include "../IWindow.h"
#include "GLFW/glfw3.h"


class GLFWWindow : public IWindow {
    std::optional<GLFWwindow*> glfwWindow;
public:
    bool initialize() override;
    bool createWindow(int width, int height, const char* window_name) override;
    [[nodiscard]] bool shouldClose() const override;
    void pollEvents() override;
    void swapBuffers() override;
    bool shutdown() override;
};


#endif //DNDCREATOR_GLFWWINDOW_H