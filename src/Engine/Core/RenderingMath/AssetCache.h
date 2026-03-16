//
// Created by Terrarizer on 15/03/2026.
//

#ifndef SESSIONZERO_ASSETCACHE_H
#define SESSIONZERO_ASSETCACHE_H
#include <memory>
#include <string>
#include <unordered_map>

#include "Mesh/Mesh.h"

struct AssetCache {
    std::unordered_map<std::string, std::shared_ptr<Mesh>> loaded_meshes;
};

#endif //SESSIONZERO_ASSETCACHE_H