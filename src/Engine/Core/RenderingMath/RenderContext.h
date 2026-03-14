//
// Created by Terrarizer on 06/03/2026.
//

#ifndef DNDCREATOR_RENDERCONTEXT_H
#define DNDCREATOR_RENDERCONTEXT_H
#include "../Nodes/Camera.h"

struct RenderContext {
    const Camera* camera = nullptr;
    zeroMath::Vector3 lightDir = { 0.0f, 0.0f, 0.0f };
};

#endif //DNDCREATOR_RENDERCONTEXT_H