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
    void deleteObject(MapData& mapData, const std::string& objUUID);
}

#endif //SESSIONZERO_TOOLS_H