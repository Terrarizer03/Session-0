//
// Created by Terrarizer on 01/02/2026.
//

#ifndef SESSIONZERO_CAMERA_H
#define SESSIONZERO_CAMERA_H

#include <cmath>

#include "../Math/Matrix/Matrix4.h"
#include "../Math/Vector/Vector3/Vector3.h"
#include "../RenderingMath/Ray.h"

struct Camera {
    zeroMath::Vector3 position, front, up;
    float fov = 0.0f, aspect = 0.0f, near = 0.0f, far = 0.0f;
    float yaw = -90.0f;
    float pitch = 0.0f;

    Camera(zeroMath::Vector3 _position)
        : position(_position), front(zeroMath::Vector3(0.0f, 0.0f, -1.0f)), up(zeroMath::Vector3(0.0f, 1.0f, 0.0f)) {}

    void updateFront();

    [[nodiscard]] zeroMath::Matrix4 getViewMatrix() const;

    [[nodiscard]] zeroMath::Matrix4 getProjectionMatrix() const;

    void setPerspective(float _fov, float _aspect, float _near, float _far);

    [[nodiscard]] Ray screenPointToRay(float mouseX, float mouseY, float windowWidth, float windowHeight) const;
};

#endif //SESSIONZERO_CAMERA_H