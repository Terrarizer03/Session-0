//
// Created by Terrarizer on 19/03/2026.
//

#include "SceneObject.h"
#include <cfloat>

void SceneObject::update() {
    if (!isDirty) return;
    if (!mesh) return;

    zeroMath::Matrix4 model = transform.getModelMatrix();

    // All 8 corners of the local box
    zeroMath::Vector3 corners[8] = {
        {mesh->localExtentsMin.x, mesh->localExtentsMin.y, mesh->localExtentsMin.z},
        {mesh->localExtentsMax.x, mesh->localExtentsMin.y, mesh->localExtentsMin.z},
        {mesh->localExtentsMin.x, mesh->localExtentsMax.y, mesh->localExtentsMin.z},
        {mesh->localExtentsMax.x, mesh->localExtentsMax.y, mesh->localExtentsMin.z},
        {mesh->localExtentsMin.x, mesh->localExtentsMin.y, mesh->localExtentsMax.z},
        {mesh->localExtentsMax.x, mesh->localExtentsMin.y, mesh->localExtentsMax.z},
        {mesh->localExtentsMin.x, mesh->localExtentsMax.y, mesh->localExtentsMax.z},
        {mesh->localExtentsMax.x, mesh->localExtentsMax.y, mesh->localExtentsMax.z},
    };

    zeroMath::Vector3 newMin = { FLT_MAX,  FLT_MAX,  FLT_MAX };
    zeroMath::Vector3 newMax = { -FLT_MAX, -FLT_MAX, -FLT_MAX };

    for (const auto& corner : corners) {
        // Transform corner by model matrix
        zeroMath::Vector4 transformed = model * zeroMath::Vector4{corner.x, corner.y, corner.z, 1.0f};

        newMin.x = std::min(newMin.x, transformed.x);
        newMin.y = std::min(newMin.y, transformed.y);
        newMin.z = std::min(newMin.z, transformed.z);
        newMax.x = std::max(newMax.x, transformed.x);
        newMax.y = std::max(newMax.y, transformed.y);
        newMax.z = std::max(newMax.z, transformed.z);
    }

    aabb.min = newMin;
    aabb.max = newMax;

    std::vector<zeroMath::Vector3> points = {
        // bottom face
        {newMin.x, newMin.y, newMin.z}, {newMax.x, newMin.y, newMin.z},
        {newMax.x, newMin.y, newMin.z}, {newMax.x, newMin.y, newMax.z},
        {newMax.x, newMin.y, newMax.z}, {newMin.x, newMin.y, newMax.z},
        {newMin.x, newMin.y, newMax.z}, {newMin.x, newMin.y, newMin.z},
        // top face
        {newMin.x, newMax.y, newMin.z}, {newMax.x, newMax.y, newMin.z},
        {newMax.x, newMax.y, newMin.z}, {newMax.x, newMax.y, newMax.z},
        {newMax.x, newMax.y, newMax.z}, {newMin.x, newMax.y, newMax.z},
        {newMin.x, newMax.y, newMax.z}, {newMin.x, newMax.y, newMin.z},
        // verticals
        {newMin.x, newMin.y, newMin.z}, {newMin.x, newMax.y, newMin.z},
        {newMax.x, newMin.y, newMin.z}, {newMax.x, newMax.y, newMin.z},
        {newMax.x, newMin.y, newMax.z}, {newMax.x, newMax.y, newMax.z},
        {newMin.x, newMin.y, newMax.z}, {newMin.x, newMax.y, newMax.z},
    };

    aabbMesh = std::make_shared<LineMesh>(points);

    isDirty = false;
}

// void SceneObject::update() {
//     if (!isDirty) return;
//
//     zeroMath::Vector3 pos = transform.position;
//     zeroMath::Vector3 scale = transform.scale;
//
//     aabb.min = { pos.x - (scale.x / 2.0f), pos.y - (scale.y / 2.0f), pos.z - (scale.z / 2.0f) };
//     aabb.max = { pos.x + (scale.x / 2.0f), pos.y + (scale.y / 2.0f), pos.z + (scale.z / 2.0f) };
//
//     isDirty = false;
// }