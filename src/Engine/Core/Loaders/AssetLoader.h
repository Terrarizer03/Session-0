//
// Created by Terrarizer on 05/03/2026.
//

#ifndef SESSIONZERO_OBJLOADER_H
#define SESSIONZERO_OBJLOADER_H

#include <string>
#include "Core/RenderingMath/Mesh/Mesh.h"
#include "Core/RenderingMath/AssetCache.h"

namespace zeroAssetLoader {
    std::string readFile(const std::string& path);
    Mesh loadOBJ(const std::string& path);
    std::shared_ptr<Mesh> getOrLoadMesh(const std::string& path, AssetCache& meshCache);

    // TODO: Make actual loaders that add objects to the scene
}

#endif //SESSIONZERO_OBJLOADER_H