//
// Created by Terrarizer on 21/01/2026.
//

#ifndef SESSIONZERO_GLFWWINDOW_H
#define SESSIONZERO_GLFWWINDOW_H

#include "../IWindow.h"
#include "GLFW/glfw3.h"

class GLFWWindow : public IWindow {
    GLFWwindow* glfwWindow = nullptr;
public:
    bool initialize() override;
    bool setVSync(bool isOn) override;
    bool createWindow(int width, int height, const char* window_name) override;
    [[nodiscard]] bool shouldClose() const override;
    void pollEvents() override;
    void swapBuffers() override;
    bool shutdown() override;

    [[nodiscard]] GLFWwindow* getHandle() const override { return glfwWindow; }
};


#endif //SESSIONZERO_GLFWWINDOW_H