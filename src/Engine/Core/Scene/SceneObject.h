//
// Created by Terrarizer on 06/03/2026.
//

#ifndef SESSIONZERO_SCENEOBJECT_H
#define SESSIONZERO_SCENEOBJECT_H
#include <string>
#include "../RenderingMath/Material.h"
#include "../RenderingMath/Transform.h"
#include "../RenderingMath/Mesh/Mesh.h"

struct SceneObject {
    // Mesh-related
    std::shared_ptr<Mesh> mesh;
    std::string meshPath;

    // Transform-related
    Transform transform;

    // Material-related
    Material material;

    // Object-related
    std::string name;
    std::string UUID;

    [[nodiscard]] const std::string& getUUID() const { return UUID; }
};

#endif //SESSIONZERO_SCENEOBJECT_H