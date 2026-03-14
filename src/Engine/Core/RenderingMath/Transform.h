//
// Created by Terrarizer on 06/03/2026.
//

#ifndef SESSIONZERO_TRANSFORM_H
#define SESSIONZERO_TRANSFORM_H
#include "../Math/Matrix/Matrix4.h"
#include "../Math/Vector/Vector3/Vector3.h"

struct Transform {
    zeroMath::Vector3 position = { 0.0f, 0.0f, 0.0f };
    zeroMath::Vector3 rotation = { 0.0f, 0.0f, 0.0f };
    zeroMath::Vector3 scale = { 1.0f, 1.0f, 1.0f };

    [[nodiscard]] zeroMath::Matrix4 getModelMatrix() const {
        const zeroMath::Matrix4 t = zeroMath::Matrix4::translate(position);
        const zeroMath::Matrix4 rx = zeroMath::Matrix4::rotate(rotation.x, { 1, 0, 0 });
        const zeroMath::Matrix4 ry = zeroMath::Matrix4::rotate(rotation.y, { 0, 1, 0 });
        const zeroMath::Matrix4 rz = zeroMath::Matrix4::rotate(rotation.z, { 0, 0, 1 });
        const zeroMath::Matrix4 s = zeroMath::Matrix4::scale(scale);

        return t * ry * rx * rz * s;
    }
};

#endif //SESSIONZERO_TRANSFORM_H