//
// Created by Terrarizer on 21/01/2026.
//

#ifndef DNDCREATOR_IRENDERER_H
#define DNDCREATOR_IRENDERER_H
#include "../Core/Rendering Math/Transform.h"
#include "../Core/Rendering Math/Mesh/Mesh.h"
#include "../Core/Rendering Math/Material.h"
#include "../Core/Rendering Math/RenderContext.h"

class IRenderer {
public:
    int window_width = 0;
    int window_height = 0;

    virtual ~IRenderer() = default;

    virtual bool initialize() = 0;
    virtual bool setViewport(int _x, int _y, int _width, int _height) = 0;
    virtual bool clearColor(float _r, float _g, float _b, float _a) = 0;
    virtual void draw(const Mesh& mesh, const Transform& transform, const Material& material, const RenderContext& context) = 0;
};

#endif //DNDCREATOR_IRENDERER_H