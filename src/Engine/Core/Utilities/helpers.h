//
// Created by Terrarizer on 16/03/2026.
//

#ifndef SESSIONZERO_HELPERS_H
#define SESSIONZERO_HELPERS_H
#include "nlohmann/json.hpp"
#include "../RenderingMath/Material.h"
#include "../RenderingMath/Transform.h"

namespace zeroHelpers {
    Material parseMaterial(const nlohmann::json& mat, const std::string& basePath);
    Transform parseTransform(const nlohmann::json& trans);
    std::string toLower(const std::string& str);
    std::string getCurrentTime();
}


#endif //SESSIONZERO_HELPERS_H