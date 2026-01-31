//
// Created by Terrarizer on 21/01/2026.
//

#ifndef DNDCREATOR_IRENDERER_H
#define DNDCREATOR_IRENDERER_H

class IRenderer {
public:
    virtual ~IRenderer() = default;

    virtual bool initialize() = 0;
    virtual bool setViewport(int _x, int _y, int _width, int _height) = 0;
    virtual bool clearColor(float _r, float _g, float _b, float _a) = 0;
};

#endif //DNDCREATOR_IRENDERER_H