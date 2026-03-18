//
// Created by Terrarizer on 21/01/2026.
//

#ifndef SESSIONZERO_GLRENDERER_H
#define SESSIONZERO_GLRENDERER_H

#include "../IRenderer.h"
#include "../../Core/Scene/RenderMode.h"

class GLRenderer : public IRenderer {
    RenderMode m_currentMode = RenderMode::SOLID;
public:
    bool initialize() override;

    bool setViewport(int _x, int _y, int _width, int _height) override;
    bool clearColor(float _r, float _g, float _b, float _a) override;

    void beginFrame() const override;
    void draw(const Mesh& mesh, const Transform& transform, const Material& material, const RenderContext& context) override;

    void setRenderMode(RenderMode renderMode) override;
};


#endif //SESSIONZERO_GLRENDERER_H