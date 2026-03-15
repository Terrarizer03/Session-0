//
// Created by Terrarizer on 21/01/2026.
//

#include <glad/glad.h>
#include "GLRenderer.h"

bool GLRenderer::initialize() {
    if (!gladLoadGL()) {
        return false;
    }

    glEnable(GL_DEPTH_TEST);

    return true;
}

bool GLRenderer::setViewport(int _x, int _y, int _width, int _height) {
    window_width = _width;
    window_height = _height;

    glViewport(_x, _y, _width, _height);

    return true;
}

bool GLRenderer::clearColor(float _r, float _g, float _b, float _a) {
    glClearColor(_r, _g, _b, _a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    return true;
}

void GLRenderer::draw(const Mesh& mesh, const Transform& transform, const Material& material, const RenderContext& context) {
    material.shader->bind();

    material.shader->setUniformVec4("uColor", material.color);
    material.shader->setUniformVec3("uLightDir", context.lightDir );

    zeroMath::Matrix4 model = transform.getModelMatrix();
    zeroMath::Matrix4 mvp = context.camera->getProjectionMatrix() * context.camera->getViewMatrix() * model;

    material.shader->setUniformMatrix4fv("uMVP", mvp);
    material.shader->setUniformMatrix4fv("uModel", model);

    mesh.draw();
}
