//
// Created by Terrarizer on 18/03/2026.
//

#include "Camera.h"

#include "../Math/Vector/Vector4.h"

void Camera::updateFront() {
    zeroMath::Vector3 direction;
    direction.x = std::cos(yaw   * (3.14159f / 180.0f)) * std::cos(pitch * (3.14159f / 180.0f));
    direction.y = std::sin(pitch * (3.14159f / 180.0f));
    direction.z = std::sin(yaw   * (3.14159f / 180.0f)) * std::cos(pitch * (3.14159f / 180.0f));
    front = direction.normalized();
}

[[nodiscard]] zeroMath::Matrix4 Camera::getViewMatrix() const {
    return zeroMath::Matrix4::lookAt(position, position + front, up);
}

[[nodiscard]] zeroMath::Matrix4 Camera::getProjectionMatrix() const {
    return zeroMath::Matrix4::perspective(fov, aspect, near, far);
}

void Camera::setPerspective(const float _fov, const float _aspect, const float _near, const float _far) {
    this->fov = _fov;
    this->aspect = _aspect;
    this->near = _near;
    this->far = _far;
}

[[nodiscard]] Ray Camera::screenPointToRay(float mouseX, float mouseY, float windowWidth, float windowHeight) const {
    // 1. NDC
    float x = (2.0f * mouseX) / windowWidth - 1.0f;
    float y = 1.0f - (2.0f * mouseY) / windowHeight;

    // 2. Clip Space
    zeroMath::Vector4 rayClip = { x, y, -1.0f, 1.0f };

    // 3. Eye Space
    zeroMath::Vector4 rayEye = getProjectionMatrix().inverse() * rayClip;
    // We want a direction pointing forward, so Z is -1, and W is 0 for a vector
    rayEye = { rayEye.x, rayEye.y, -1.0f, 0.0f };

    // 4. World Space
    zeroMath::Vector4 worldDir4 = getViewMatrix().inverse() * rayEye;

    // Convert to Vector3 and normalize
    zeroMath::Vector3 rayDirection = { worldDir4.x, worldDir4.y, worldDir4.z };
    rayDirection = rayDirection.normalized(); // Make sure .normalized() returns a new vector or modifies it correctly

    return { position, rayDirection };
}
