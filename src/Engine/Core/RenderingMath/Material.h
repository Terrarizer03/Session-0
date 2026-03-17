//
// Created by Terrarizer on 06/03/2026.
//

#ifndef SESSIONZERO_MATERIAL_H
#define SESSIONZERO_MATERIAL_H
#include <memory>
#include "../../Renderer/IShader.h"
#include "../Math/Vector/Vector4.h"

struct Material {
    std::shared_ptr<IShader> shader;
    zeroMath::Vector4 color;
    std::string vertexPath;
    std::string fragmentPath;
};

#endif //SESSIONZERO_MATERIAL_H