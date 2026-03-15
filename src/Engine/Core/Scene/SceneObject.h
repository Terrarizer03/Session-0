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
    std::shared_ptr<Mesh> mesh;
    Transform transform;
    Material material;
    std::string name;
    std::string UUID;
};

#endif //SESSIONZERO_SCENEOBJECT_H