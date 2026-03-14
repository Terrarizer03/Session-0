//
// Created by Terrarizer on 14/03/2026.
//

#ifndef SESSIONZERO_UIMANAGER_H
#define SESSIONZERO_UIMANAGER_H

struct GLFWwindow;

struct UIManager {
    void initialize(GLFWwindow*);
    void beginFrame();
    void endFrame();
    void shutdown();
};


#endif //SESSIONZERO_UIMANAGER_H