//
// Created by Terrarizer on 21/01/2026.
//

#include <glad/glad.h>
#include "GLRenderer.h"

#include "GLFW/glfw3.h"

bool GLRenderer::initialize() {
    if (!gladLoadGL()) {
        return false;
    }

    return true;
}

bool GLRenderer::setViewport(int _x, int _y, int _width, int _height) {
    glViewport(_x, _y, _width, _height);

    return true;
}

bool GLRenderer::clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    return true;
}

bool GLRenderer::clearColor(float _r, float _g, float _b, float _a) {
    glClearColor(_r, _g, _b, _a);

    return true;
}
