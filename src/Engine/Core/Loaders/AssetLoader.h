//
// Created by Terrarizer on 05/03/2026.
//

#ifndef DNDCREATOR_OBJLOADER_H
#define DNDCREATOR_OBJLOADER_H

#include <string>
#include "../RenderingMath/Mesh/Mesh.h"

namespace zeroAssetLoader {
    std::string readFile(const std::string& path);
    Mesh loadOBJ(const std::string& path);

    // TODO: Make actual loaders that add objects to the scene
}

#endif //DNDCREATOR_OBJLOADER_H