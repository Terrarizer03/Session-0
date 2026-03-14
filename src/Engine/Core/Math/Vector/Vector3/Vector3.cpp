//
// Created by Terrarizer on 04/03/2026.
//

#include "Vector3.h"
#include <cmath>

using zeroMath::Vector3;

[[nodiscard]] Vector3 Vector3::normalized() const {
    float magnitude = std::sqrt(x * x + y * y + z * z);
    if (magnitude < 1e-6f) return Vector3(0.0f, 0.0f, 0.0f);
    return Vector3(x / magnitude, y / magnitude, z / magnitude);
}

[[nodiscard]] Vector3 Vector3::cross(const Vector3& other) const {
    return {
        y * other.z - z * other.y,
        z * other.x - x * other.z,
        x * other.y - y * other.x
    };
}

[[nodiscard]] float Vector3::dot(const Vector3& other) const {
    return (x * other.x) + (y * other.y) + (z * other.z);
}
