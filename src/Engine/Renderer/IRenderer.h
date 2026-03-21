//
// Created by Terrarizer on 21/01/2026.
//

#ifndef SESSIONZERO_IRENDERER_H
#define SESSIONZERO_IRENDERER_H
#include "Core/Physics/Collision.h"
#include "Core/RenderingMath/Transform.h"
#include "Core/RenderingMath/Mesh/Mesh.h"
#include "Core/RenderingMath/Material.h"
#include "Core/RenderingMath/Mesh/LineMesh.h"
#include "Core/Scene/RenderContext.h"
#include "Core/Scene/RenderMode.h"

class IRenderer {
public:
    int window_width = 0;
    int window_height = 0;

    virtual ~IRenderer() = default;

    virtual bool initialize() = 0;
    virtual bool setViewport(int _x, int _y, int _width, int _height) = 0;
    virtual bool clearColor(float _r, float _g, float _b, float _a) = 0;
    virtual void beginFrame() const = 0;
    virtual void draw(const Mesh& mesh, const Transform& transform, const Material& material, const RenderContext& context) = 0;
    virtual void drawAABB(const LineMesh& aabbMesh, const RenderContext& context) = 0;
    virtual void drawRay(const Ray& ray, float length, const RenderContext& context) = 0;

    virtual void setRenderMode(int mode) = 0;
};

#endif //SESSIONZERO_IRENDERER_H