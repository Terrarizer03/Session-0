//
// Created by Terrarizer on 06/03/2026.
//

#ifndef DNDCREATOR_MATERIAL_H
#define DNDCREATOR_MATERIAL_H
#include <memory>
#include "../../Renderer/IShader.h"
#include "../Math/Vector/Vector4.h"

struct Material {
    std::shared_ptr<IShader> shader;
    dndMath::Vector4 color;
};

#endif //DNDCREATOR_MATERIAL_H