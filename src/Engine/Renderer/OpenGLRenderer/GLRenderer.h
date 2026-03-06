//
// Created by Terrarizer on 21/01/2026.
//

#ifndef DNDCREATOR_GLRENDERER_H
#define DNDCREATOR_GLRENDERER_H

#include "../IRenderer.h"

class GLRenderer : public IRenderer {
public:
    bool initialize() override;

    bool setViewport(int _x, int _y, int _width, int _height) override;
    bool clearColor(float _r, float _g, float _b, float _a) override;

    void draw(const Mesh& mesh, const Transform& transform, const Material& material, const RenderContext& context) override;
};


#endif //DNDCREATOR_GLRENDERER_H