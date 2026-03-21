//
// Created by Terrarizer on 16/03/2026.
//

#ifndef SESSIONZERO_HELPERS_H
#define SESSIONZERO_HELPERS_H
#include "nlohmann/json.hpp"
#include "Core/RenderingMath/Material.h"
#include "Core/RenderingMath/Transform.h"
#include "Core/Project/MapData.h"

namespace zeroHelpers {
    Material parseMaterial(const nlohmann::json& mat, const std::string& basePath);
    Transform parseTransform(const nlohmann::json& trans);
    std::string toLower(const std::string& str);
    std::string getCurrentTime();
    std::string resolvePath(const std::string& meshPath, const std::string& mapFolder);
    std::string generateUniqueName(const std::string& baseName, const MapData& mapData);
}


#endif //SESSIONZERO_HELPERS_H