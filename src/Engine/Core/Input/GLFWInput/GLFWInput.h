//
// Created by Terrarizer on 05/03/2026.
//

#ifndef SESSIONZERO_GLFWINPUT_H
#define SESSIONZERO_GLFWINPUT_H

#include "../IInput.h"
#include "GLFW/glfw3.h"

class GLFWInput : public IInput {
    GLFWwindow* m_handle;
    double m_LastX = 400, m_LastY = 400;
    bool m_FirstMouse = true;
    float m_DeltaX = 0, m_DeltaY = 0;
    bool m_prevKeys[GLFW_KEY_LAST] = {};
    bool m_currKeys[GLFW_KEY_LAST] = {};
public:
    explicit GLFWInput(GLFWwindow* handle) : m_handle(handle) {}

    [[nodiscard]] bool getKey(int key) const override {
        return m_currKeys[key];
    }
    [[nodiscard]] bool getKeyPressed(int key) const override {
        return m_currKeys[key] && !m_prevKeys[key];
    }
    [[nodiscard]] bool getMouseButton(int button) const override {
        return glfwGetMouseButton(m_handle, button) == GLFW_PRESS;
    }
    void resetMouseDelta() override {
        m_FirstMouse = true;
    }
    void getMousePosition(double &x, double &y) const override {
        glfwGetCursorPos(m_handle, &x, &y);
    }

    void setCursorMode(bool enabled) override {
        glfwSetInputMode(m_handle, GLFW_CURSOR, enabled ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
    }

    void update() override {
        std::copy(std::begin(m_currKeys), std::end(m_currKeys), std::begin(m_prevKeys));

        for (int i = 0; i < GLFW_KEY_LAST; i++) {
            m_currKeys[i] = glfwGetKey(m_handle, i) == GLFW_PRESS;
        }

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


#endif //SESSIONZERO_GLFWINPUT_H