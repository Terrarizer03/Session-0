//
// Created by Terrarizer on 06/03/2026.
//

#ifndef SESSIONZERO_SCENEOBJECT_H
#define SESSIONZERO_SCENEOBJECT_H
#include <string>
#include "Core/Physics/Collision.h"
#include "Core/RenderingMath/Material.h"
#include "Core/RenderingMath/Transform.h"
#include "Core/RenderingMath/Mesh/LineMesh.h"
#include "Core/RenderingMath/Mesh/Mesh.h"

struct SceneObject {
    // Mesh-related
    std::shared_ptr<Mesh> mesh = nullptr;
    std::shared_ptr<LineMesh> aabbMesh = nullptr; // Will be applied soon
    std::string meshPath;

    // Transform-related
    Transform transform{};
    zeroMath::Vector3 localExtentsMax{}, localExtentsMin{};

    // Material-related
    Material material{};

    // Object-related
    std::string name;
    std::string UUID;
    zeroPhysics::AABB aabb{}; // Temporary
    bool isDirty = true;

    void update();

    [[nodiscard]] const std::string& getUUID() const { return UUID; }
};

#endif //SESSIONZERO_SCENEOBJECT_H