//
// Created by Terrarizer on 06/03/2026.
//

#ifndef DNDCREATOR_SCENEOBJECT_H
#define DNDCREATOR_SCENEOBJECT_H
#include <string>

#include "Material.h"
#include "Transform.h"
#include "Mesh/Mesh.h"

struct SceneObject {
    std::shared_ptr<Mesh> mesh;
    Transform transform;
    Material material;
    std::string name;
    std::string UUID;
};

#endif //DNDCREATOR_SCENEOBJECT_H