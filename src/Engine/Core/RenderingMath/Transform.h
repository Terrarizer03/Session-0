//
// Created by Terrarizer on 06/03/2026.
//

#ifndef DNDCREATOR_TRANSFORM_H
#define DNDCREATOR_TRANSFORM_H
#include "../Math/Matrix/Matrix4.h"
#include "../Math/Vector/Vector3/Vector3.h"

struct Transform {
    dndMath::Vector3 position = { 0.0f, 0.0f, 0.0f };
    dndMath::Vector3 rotation = { 0.0f, 0.0f, 0.0f };
    dndMath::Vector3 scale = { 1.0f, 1.0f, 1.0f };

    [[nodiscard]] dndMath::Matrix4 getModelMatrix() const {
        const dndMath::Matrix4 t = dndMath::Matrix4::translate(position);
        const dndMath::Matrix4 rx = dndMath::Matrix4::rotate(rotation.x, { 1, 0, 0 });
        const dndMath::Matrix4 ry = dndMath::Matrix4::rotate(rotation.y, { 0, 1, 0 });
        const dndMath::Matrix4 rz = dndMath::Matrix4::rotate(rotation.z, { 0, 0, 1 });
        const dndMath::Matrix4 s = dndMath::Matrix4::scale(scale);

        return t * ry * rx * rz * s;
    }
};

#endif //DNDCREATOR_TRANSFORM_H