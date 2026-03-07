//
// Created by Terrarizer on 05/03/2026.
//

#ifndef DNDCREATOR_GLFWINPUT_H
#define DNDCREATOR_GLFWINPUT_H

#include "../IInput.h"
#include "GLFW/glfw3.h"

class GLFWInput : public IInput {
    GLFWwindow* m_handle;
    double m_LastX = 400, m_LastY = 400;
    bool m_FirstMouse = true;
    float m_DeltaX = 0, m_DeltaY = 0;
public:
    explicit GLFWInput(GLFWwindow* handle) : m_handle(handle) {}

    [[nodiscard]] bool getKey(int key) const override {
        return glfwGetKey(m_handle, key) == GLFW_PRESS;
    }
    [[nodiscard]] bool getMouseButton(int button) const override {
        return glfwGetMouseButton(m_handle, button) == GLFW_PRESS;
    }
    void getMousePosition(double &x, double &y) const override {
        glfwGetCursorPos(m_handle, &x, &y);
    }

    void update() override {
        double x, y;
        glfwGetCursorPos(m_handle, &x, &y);

        if (m_FirstMouse) {
            m_LastX = x;
            m_LastY = y;
            m_FirstMouse = false;
        }

        m_DeltaX = (float)(x - m_LastX);
        m_DeltaY = (float)(m_LastY - y); // reversed - y goes bottom to top
        m_LastX = x;
        m_LastY = y;
    }

    [[nodiscard]] float getDeltaX() const override { return m_DeltaX; }
    [[nodiscard]] float getDeltaY() const override { return m_DeltaY; }
};


#endif //DNDCREATOR_GLFWINPUT_H