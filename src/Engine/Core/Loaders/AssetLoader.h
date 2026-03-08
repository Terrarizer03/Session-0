//
// Created by Terrarizer on 05/03/2026.
//

#ifndef DNDCREATOR_OBJLOADER_H
#define DNDCREATOR_OBJLOADER_H

#include <string>
#include "../Rendering Math/Mesh/Mesh.h"

namespace dndAssetLoader {
    std::string readFile(const std::string& path);
    Mesh loadOBJ(const std::string& path);
}

#endif //DNDCREATOR_OBJLOADER_H