//
// Created by Terrarizer on 21/01/2026.
//

#ifndef SESSIONZERO_GLRENDERER_H
#define SESSIONZERO_GLRENDERER_H

#include "Core/Utilities/constants.h"
#include "Renderer/IRenderer.h"

class GLRenderer : public IRenderer {
    std::shared_ptr<IShader> m_debugShader;
    int m_currentMode = zeroConstants::SOLID_MODE;
public:
    bool initialize() override;

    bool setViewport(int _x, int _y, int _width, int _height) override;
    bool clearColor(float _r, float _g, float _b, float _a) override;

    void beginFrame() const override;
    void draw(const Mesh& mesh, const Transform& transform, const Material& material, const RenderContext& context) override;
    void drawAABB(const LineMesh &aabbMesh, const RenderContext &context) override;
    void drawRay(const Ray &ray, float length, const RenderContext &context) override;

    void setRenderMode(int mode) override;
};


#endif //SESSIONZERO_GLRENDERER_H