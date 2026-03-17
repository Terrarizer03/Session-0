//
// Created by Terrarizer on 15/03/2026.
//

#ifndef SESSIONZERO_TOOLS_H
#define SESSIONZERO_TOOLS_H
#include "MapData.h"

enum struct Primitive {
    SPHERE,
    CUBE,
    PLANE
};

namespace zeroTools {
    void addPrimitive(MapData& mapData, Primitive primitive);
    void addSphereObject(MapData& mapData, const std::string& projectPath, const std::string& mapName);
    void addCubeObject(MapData& mapData, const std::string& projectPath, const std::string& mapName);
}

#endif //SESSIONZERO_TOOLS_H