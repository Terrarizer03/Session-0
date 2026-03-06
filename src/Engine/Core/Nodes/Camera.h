//
// Created by Terrarizer on 01/02/2026.
//

#ifndef DNDCREATOR_CAMERA_H
#define DNDCREATOR_CAMERA_H

#include <cmath>

#include "../Math/Matrix/Matrix4.h"
#include "../Math/Vector/Vector3/Vector3.h"

struct Camera {
    dndMath::Vector3 position, front, up;
    float fov = 0.0f, aspect = 0.0f, near = 0.0f, far = 0.0f;
    float yaw = -90.0f;
    float pitch = 0.0f;

    Camera(dndMath::Vector3 _position)
        : position(_position), front(dndMath::Vector3(0.0f, 0.0f, -1.0f)), up(dndMath::Vector3(0.0f, 1.0f, 0.0f)) {}

    void updateFront() {
        dndMath::Vector3 direction;
        direction.x = std::cos(yaw   * (3.14159f / 180.0f)) * std::cos(pitch * (3.14159f / 180.0f));
        direction.y = std::sin(pitch * (3.14159f / 180.0f));
        direction.z = std::sin(yaw   * (3.14159f / 180.0f)) * std::cos(pitch * (3.14159f / 180.0f));
        front = direction.normalized();
    }

    [[nodiscard]] dndMath::Matrix4 getViewMatrix() const {
        return dndMath::Matrix4::lookAt(position, position + front, up);
    }

    [[nodiscard]] dndMath::Matrix4 getProjectionMatrix() const {
        return dndMath::Matrix4::perspective(fov, aspect, near, far);
    }

    void setPerspective(const float _fov, const float _aspect, const float _near, const float _far) {
        this->fov = _fov;
        this->aspect = _aspect;
        this->near = _near;
        this->far = _far;
    }
};

#endif //DNDCREATOR_CAMERA_H