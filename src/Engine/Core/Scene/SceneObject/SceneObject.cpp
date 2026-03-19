//
// Created by Terrarizer on 19/03/2026.
//

#include "SceneObject.h"

void SceneObject::update() {
    if (!isDirty) return;

    zeroMath::Vector3 pos = transform.position;
    zeroMath::Vector3 scale = transform.scale;

    aabb.min = { pos.x - (scale.x / 2.0f), pos.y - (scale.y / 2.0f), pos.z - (scale.z / 2.0f) };
    aabb.max = { pos.x + (scale.x / 2.0f), pos.y + (scale.y / 2.0f), pos.z + (scale.z / 2.0f) };

    isDirty = false;
}