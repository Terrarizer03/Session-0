//
// Created by Terrarizer on 03/03/2026.
//

#ifndef DNDCREATOR_VECTOR4_H
#define DNDCREATOR_VECTOR4_H

namespace dndMath {
    struct Vector4 {
        float x, y, z, w;

        constexpr Vector4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}

        constexpr Vector4(const float _x, const float _y, const float _z, const float _w) : x(_x), y(_y), z(_z), w(_w) {}

        Vector4 operator+(const Vector4 &other) const {
            return { x + other.x, y + other.y, z + other.z, w + other.w };
        }
        Vector4 operator-(const Vector4 &other) const {
            return { other.x - x, other.y - y, other.z - z, other.w - w };
        }
        Vector4 operator*(const float scalar) const {
            return { x * scalar, y * scalar, z * scalar, w * scalar };
        }
        Vector4 operator*(const Vector4 &other) const {
            return { other.x * x, other.y * y, other.z * z, other.w * w };
        }
    };

    inline Vector4 operator*(const float scalar, const Vector4 vector) {
        return vector * scalar;
    }
}

#endif //DNDCREATOR_VECTOR4_H