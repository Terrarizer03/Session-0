//
// Created by Terrarizer on 01/02/2026.
//

#ifndef SESSIONZERO_CAMERA_H
#define SESSIONZERO_CAMERA_H

#include <cmath>

#include "../Math/Matrix/Matrix4.h"
#include "../Math/Vector/Vector3/Vector3.h"

struct Camera {
    zeroMath::Vector3 position, front, up;
    float fov = 0.0f, aspect = 0.0f, near = 0.0f, far = 0.0f;
    float yaw = -90.0f;
    float pitch = 0.0f;

    Camera(zeroMath::Vector3 _position)
        : position(_position), front(zeroMath::Vector3(0.0f, 0.0f, -1.0f)), up(zeroMath::Vector3(0.0f, 1.0f, 0.0f)) {}

    void updateFront() {
        zeroMath::Vector3 direction;
        direction.x = std::cos(yaw   * (3.14159f / 180.0f)) * std::cos(pitch * (3.14159f / 180.0f));
        direction.y = std::sin(pitch * (3.14159f / 180.0f));
        direction.z = std::sin(yaw   * (3.14159f / 180.0f)) * std::cos(pitch * (3.14159f / 180.0f));
        front = direction.normalized();
    }

    [[nodiscard]] zeroMath::Matrix4 getViewMatrix() const {
        return zeroMath::Matrix4::lookAt(position, position + front, up);
    }

    [[nodiscard]] zeroMath::Matrix4 getProjectionMatrix() const {
        return zeroMath::Matrix4::perspective(fov, aspect, near, far);
    }

    void setPerspective(const float _fov, const float _aspect, const float _near, const float _far) {
        this->fov = _fov;
        this->aspect = _aspect;
        this->near = _near;
        this->far = _far;
    }
};

#endif //SESSIONZERO_CAMERA_H